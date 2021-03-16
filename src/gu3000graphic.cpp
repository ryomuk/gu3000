// Library for Noritake Itron GU-3000 Series VFD
// Parallel Interface Graphic DMA Command Mode

#include <stdio.h>
#include <stdlib.h>
#include "gu3000graphic.h"

void GU3000Graphic::init(int x, int y, int memsize, word DAD){
  xsize = x;
  ysize = y;
  m_disp_memsize  = memsize;
  m_disp_areasize = xsize * ysize / 8;
    
  FrameBuffer::init(xsize, ysize);

  m_buf = (byte *)realloc(m_buf, m_disp_memsize);
  m_first_show = true;

  setDAD(DAD);

  flushCommandData(); // Flush last incompleted command (ex. copy large bitmap)
  setDisplayStartAddress(0);
  setDrawingAddress(0);
  setBrightness(VFD_BRIGHTNESS_MID);
}

void GU3000Graphic::setDAD(word DAD){
  m_dad = DAD;
}

void GU3000Graphic::setBitmapOrder(int order)
{
  GU3000GPIO::setBitmapOrder(order);
}

void GU3000Graphic::writeBitImage(word startAddress, word size, byte *imagedata){
  int i;
  writeCommand(0x46);
  writeWord(startAddress);
  writeWord(size);
  for(i = 0; i < size; i++){
    writeByteImage(*imagedata);
    m_buf[startAddress + i] = *imagedata;
    imagedata++;
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
}

void GU3000Graphic::syncNextCommand(){
  writeCommand(0x57);
  writeByte(0x01);
}

void GU3000Graphic::setBrightness(byte brightness){
  writeCommand(0x58);
  writeByte(brightness);
}

void GU3000Graphic::setDrawingAddress(word address){
  m_drawing_addr = address;
}

void GU3000Graphic::rotateDrawingAddress(){
  m_drawing_addr = (m_drawing_addr + m_disp_areasize) % m_disp_memsize;
}

void GU3000Graphic::setDisplayStartAddressToDrawingAddress(){
  setDisplayStartAddress(m_drawing_addr);
}

void GU3000Graphic::clear(){
  int num_display =m_disp_memsize / m_disp_areasize; 

  clearFrameBuffer();
  
  for(int i = 0; i < num_display; i++){
    setDisplayStartAddress(i * m_disp_areasize);
    showAllArea();
  }
  setDisplayStartAddress(0);
  setDrawingAddress(0);
}

void GU3000Graphic::clearFrameBuffer(){
  FrameBuffer::clear();
}

// Sending whole buffer takes time (ex. s256x128 buffer takes 12ms),
// so compare the current buffer and the last buffer before sending
// to VFD module.
void GU3000Graphic::show(){
  int i;
  int diff_start, diff_size;

  if( m_first_show ){
    m_first_show = false;
    diff_start = 0;
    diff_size = m_disp_areasize;
  } else {
    for(i = 0; i < m_disp_areasize; i++){
      if(m_drawing_addr+i >= m_disp_memsize) break;
      if(m_buf[m_drawing_addr+i] != buf[i]) break;
    }
    if(i == m_disp_areasize) return;  // m_buf == buf
    
    diff_start = i;
    
    for(i = min(m_drawing_addr + m_disp_areasize, m_disp_memsize) -1;
	i > diff_start; i--){
      if(m_buf[m_drawing_addr+i] != buf[i]) break;
    }
    diff_size = i - diff_start + 1;
  }
  
  writeBitImage(m_drawing_addr + diff_start, diff_size, &(buf[diff_start]));
}

void GU3000Graphic::rotateAndShow(){
  rotateDrawingAddress();
  show();
  setDisplayStartAddressToDrawingAddress();
}

void GU3000Graphic::syncAndShow(){
  syncNextCommand();
  show();
}

void GU3000Graphic::syncRotateAndShow(){
  rotateDrawingAddress();
  show();
  syncNextCommand();
  setDisplayStartAddressToDrawingAddress();
}

void GU3000Graphic::showAllArea(){
  m_first_show = true;
  show();
}

// Flush last incompleted command (ex. copy large bitmap)
void GU3000Graphic::flushCommandData(){
  for(int i = 0; i < m_disp_memsize ; i++){
    writeByte(0);
  }
}

//
// Graphic DMA Mode Commands
//
void GU3000Graphic::writeCommand(byte commandCode){
  writeByte(0x02); // command header 1(STX)
  writeByte(0x44); // command header 2
  writeByte(m_dad);
  writeByte(commandCode);
}
