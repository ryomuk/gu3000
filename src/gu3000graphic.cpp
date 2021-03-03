// Library for Noritake Itron GU-3000 Series VFD
// Parallel Interface Graphic DMA Command Mode

#include <stdio.h>
#include <stdlib.h>
#include "gu3000graphic.h"

//
// Graphic DMA Mode Commands
//
void GU3000Graphic::init(int x, int y, int memsize){
  xsize = x;
  ysize = y;
  m_disp_memsize  = memsize;
  m_disp_areasize = xsize * ysize / 8;
    
  FrameBuffer::init(xsize, ysize);

  flushCommandData(); // Flush last incompleted command (ex. copy large bitmap)
  setDisplayStartAddress(0);
  setBrightness(VFD_BRIGHTNESS_MID);
}

// Flush last incompleted command (ex. copy large bitmap)
void GU3000Graphic::flushCommandData(){
  for(int i = 0; i < m_disp_memsize ; i++){
    writeByte(0);
  }
}

void GU3000Graphic::setDAD(word displayAddress){
  m_dad = displayAddress;
}

void GU3000Graphic::setBitmapOrder(int order)
{
  GU3000GPIO::setBitmapOrder(order);
}

void GU3000Graphic::writeCommand(byte commandCode){
  writeByte(0x02); // command header 1(STX)
  writeByte(0x44); // command header 2
  writeByte(m_dad);
  writeByte(commandCode);
}

void GU3000Graphic::writeBitImage(word startAddress, word size, byte *imagedata){
  int i;
  writeCommand(0x46);
  writeWord(startAddress);
  writeWord(size);
  for(i = 0; i < size; i++){
    writeByteImage(*imagedata++);
  }
}

void GU3000Graphic::writeAreaBitImage(word startAddress,
				       word xbyte, word ybyte,
				       byte *imagedata){
  int i;
  writeCommand(0x42);
  writeWord(startAddress);
  writeWord(xbyte);
  writeWord(ybyte);
  for(i = 0; i < xbyte * ybyte; i++){
    writeByteImage(*imagedata++);
  }
}

void GU3000Graphic::setDisplayStartAddress(word startAddress){
  writeCommand(0x53);
  writeWord(startAddress);
  m_disp_startaddr = startAddress;
}

void GU3000Graphic::updateDisplayStartAddress(){
  setDisplayStartAddress(m_disp_startaddr);
}

void GU3000Graphic::syncNextCommand(){
  writeCommand(0x57);
  writeByte(0x01);
}

void GU3000Graphic::setBrightness(byte brightness){
  writeCommand(0x58);
  writeByte(brightness);
}

void GU3000Graphic::fillDisplay(byte writeData){
  int i;
  writeCommand(0x46); // write bit image
  writeWord(m_disp_startaddr);
  writeWord(m_disp_areasize);
  for(i = 0; i < m_disp_areasize; i++){
    writeByteImage(writeData);
  }
}  

void GU3000Graphic::clearDisplay(){
  int num_display =m_disp_memsize / m_disp_areasize; 
  
  for(int i = 0; i < num_display; i++){
    setDisplayStartAddress(i * m_disp_areasize);
    fillDisplay(i * m_disp_areasize);
  }
  setDisplayStartAddress(0);
}

//
// rename to distinguish clearDisplay
void GU3000Graphic::clearFrameBuffer(){
  FrameBuffer::clear();
}

void GU3000Graphic::rotateButNotSetDisplayStartAddress(){
  m_disp_startaddr = (m_disp_startaddr + m_disp_areasize) % m_disp_memsize;
}

void GU3000Graphic::rotateAndSetDisplayStartAddress(){
  rotateButNotSetDisplayStartAddress();
  updateDisplayStartAddress();
}

void GU3000Graphic::show(){
  int i, diff_start, diff_size;
  if(m_buf == NULL){
    m_buf = (byte *)malloc(m_disp_memsize);
    diff_start = 0;
    diff_size  = m_disp_areasize;
  } else {
    for(i = 0; i < m_disp_areasize; i++){
      if(m_disp_startaddr+i >= m_disp_memsize) break;
      if(m_buf[m_disp_startaddr+i] != buf[i]) break;
    }
    if(i == m_disp_areasize) return;  // m_buf == buf
    
    diff_start = i;

    for(i = min(m_disp_startaddr + m_disp_areasize, m_disp_memsize) -1;
	i > diff_start; i--){
      if(m_buf[m_disp_startaddr+i] != buf[i]) break;
    }
    diff_size = i - diff_start + 1;
  }
  writeBitImage(m_disp_startaddr + diff_start, diff_size, &(buf[diff_start]));
  for(i = 0; i < diff_size; i++){
    m_buf[m_disp_startaddr+diff_start+i] = buf[diff_start+i];
  }
}

void GU3000Graphic::rotateAndShow(){
  rotateButNotSetDisplayStartAddress();
  show();
  updateDisplayStartAddress();
}

void GU3000Graphic::syncAndShow(){
  syncNextCommand();
  show();
}

void GU3000Graphic::syncRotateAndShow(){
  rotateButNotSetDisplayStartAddress();
  show();
  syncNextCommand();
  updateDisplayStartAddress();
}

void GU3000Graphic::showAllArea(){
  writeBitImage(m_disp_startaddr, m_disp_areasize, buf);
}

