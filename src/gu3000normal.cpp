#include <stdio.h>
#include <stdlib.h>
#include "gu3000normal.h"

//
// Normal Mode Commands
//
void GU3000Normal::init(int x, int y, int memsize){
  xsize = x;
  ysize = y;
  m_disp_areasize = xsize * ysize / 8;
  m_ybytes = y / 8;

  FrameBuffer::init(xsize, ysize);

  setBrightness(VFD_BRIGHTNESS_MID);
}


void GU3000Normal::initialize(){
  writeByte(0x1b);
  writeByte(0x40);
}

void GU3000Normal::setBrightness(byte b){
  writeByte(0x1f);
  writeByte(0x58);
  writeByte(b);
}

void GU3000Normal::setCursorMode(byte b){ // 0:off, 1:on
  writeByte(0x1f);
  writeByte(0x43);
  writeByte(b);
}

void GU3000Normal::setCursor(word x, word y){
  writeByte(0x1f);
  writeByte(0x24);
  writeWord(x);
  writeWord(y);
}

void GU3000Normal::setScrollMode(byte b){
  writeByte(0x1f);
  writeByte(b);
}

void GU3000Normal::putchar(int c){
  writeByte(c);
}

void GU3000Normal::drawDot(int x, int y, int pen){
  if(x < 0 || x >= xsize || y < 0 || y >= ysize || pen < 0 || pen > 1){
    return;
  }
  // Draw Dot
  writeByte(0x1f);
  writeByte(0x28);
  writeByte(0x64);
  writeByte(0x10);
  writeByte(pen);
  writeWord(x);
  writeWord(y);
}

void GU3000Normal::drawLineBox(int x1, int y1, int x2, int y2,
			       int pen, int mode)
//pen=0:off, 1:on
//mode=0:line, 1:box, 2:boxfill
{
  // Draw LineBox
  writeByte(0x1f);
  writeByte(0x28);
  writeByte(0x64);
  writeByte(0x11);
  writeByte(mode);
  writeByte(pen);
  writeWord(x1);
  writeWord(y1);
  writeWord(x2);
  writeWord(y2);
}

void GU3000Normal::drawLine(int x1, int y1, int x2, int y2, int pen){
  drawLineBox(x1, y1, x2, y2, pen, 0);
}

void GU3000Normal::drawBox(int x1, int y1, int x2, int y2, int pen){
  drawLineBox(x1, y1, x2, y2, pen, 1);
}

void GU3000Normal::drawBoxFill(int x1, int y1, int x2, int y2, int pen){
  drawLineBox(x1, y1, x2, y2, pen, 2);
}

 void GU3000Normal::writeBitImage(word startAddress, word size, byte *imagedata){
  int x, y, size_x, size_y;
  
  x = startAddress / m_ybytes;
  y = startAddress % m_ybytes;
  setCursor(x, y);

  size_x = size / m_ybytes;
  size_y = m_ybytes;
  
  writeByte(0x1f);
  writeByte(0x28);
  writeByte(0x66);
  writeByte(0x11);
  writeWord(size_x);
  writeWord(size_y);
  writeByte(1);
  for(int i = 0; i < size; i++){
    writeByteImage(*imagedata++);
  }
}
void GU3000Normal::fillBuffer(word startAddress, byte writeData){
  int x, y;
  x = startAddress / m_ybytes;
  y = startAddress % m_ybytes;
  setCursor(x, y);

  writeByte(0x1f);
  writeByte(0x28);
  writeByte(0x66);
  writeByte(0x11);
  writeWord(xsize);
  writeWord(ysize);
  writeByte(1);
  for(int i = 0; i < m_disp_areasize; i++){
    writeByteImage(writeData);
  }
}

void GU3000Normal::powerMode(byte p){
  // set power mode of the display
  // 0:off, 1:on, 0x10:autoPowerOff

  writeByte(0x1f);
  writeByte(0x28);
  writeByte(0x61);
  writeByte(0x40);
  writeByte(p);
}

void GU3000Normal::autoPowerOff(byte t){
  // set auto power off time of the display
  // t * 60sec.
  // default = 0x1e (30min)
  writeByte(0x1f);
  writeByte(0x28);
  writeByte(0x61);
  writeByte(0x40);
  writeByte(0x11);
  writeByte(t);

  powerMode(VFD_DISPLAY_AUTO_POWER_OFF);
}

void GU3000Normal::clearDisplay(){
  putchar(CODE_DisplayClear);
}

//
// rename to distinguish clearDisplay
void GU3000Normal::clearFrameBuffer(){
  FrameBuffer::clear();
}

void GU3000Normal::puts(char *s){
  while(*s != '\0'){
    if(*s == '\n'){
      putchar(*s++);
      putchar('\r');
    } else {
      putchar(*s++);
    }
  }
}
