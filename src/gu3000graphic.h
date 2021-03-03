// Header file for Noritake GU-3000 Series VFD
// using Parallel Interface Graphic DMA mode
// use 'GU3000normal.h' if you use normal command mode

#ifndef GU3000GRAPHIC_H
#define GU3000GRAPHIC_H

#include "gu3000gpio.h"
#include "framebuffer.h"

//
//   Graphic DMA Command Mode
//
class GU3000Graphic : public FrameBuffer, private GU3000GPIO {
 public:
  GU3000Graphic(){
    init();
  };
  // Geometry of Visible Area
  int xsize;
  int ysize;
  //
  void init(){
    init(VFD_Xdots, VFD_Ydots, VFD_DispMemSize);
  };
  void init(int x, int y, int memsize);
  void setDAD(word displayAddress); // displayAddress(for multiple VFD);
  void setBitmapOrder(int order);
  //
  // Native Graphic DMA Commands of VFD
  //
  void setDisplayStartAddress(word displayStartAddress);
  void writeBitImage(word address,  word imagesize, byte *bitmap);
  void writeAreaBitImage(word address, word xbyte, word ybyte, byte *bitmap);
  void setBrightness(byte brightness);
  void syncNextCommand();
  //
  // Operation to VFD Display Address
  //
  void updateDisplayStartAddress();    // address = DisplayStartAddress
  void rotateAndSetDisplayStartAddress(); 
  void rotateButNotSetDisplayStartAddress();
  void fillDisplay(byte writeData);
  void clearDisplay();
  //
  // Operation to FrameBuffer
  //
  void clearFrameBuffer();
  //
  // FrameBuffer and VFD interaction
  //
  void show();
  void rotateAndShow();
  void syncAndShow();
  void syncRotateAndShow();
  void showAllArea();
private:
  //
  byte *m_buf = NULL;
  word m_disp_memsize;
  word m_disp_areasize;
  word m_disp_startaddr;
  //
  void flushCommandData();
  void writeCommand(byte command);
  // DAD(Display Address for using multiple VFD modules)
  word m_dad = VFD_DAD_BROADCAST;
};

typedef GU3000Graphic VFD;

#endif
