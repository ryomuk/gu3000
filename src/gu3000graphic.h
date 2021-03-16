#ifndef GU3000GRAPHIC_H
#define GU3000GRAPHIC_H

// gu3000graphic.h
//
// Header file for Noritake GU-3000 Series VFD
// using Parallel Interface Graphic DMA mode
// use 'GU3000normal.h' if you use normal command mode

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
    init(VFD_Xdots, VFD_Ydots, VFD_DispMemSize, VFD_DAD_BROADCAST);
  };
  void init(int x, int y, int memsize, word DAD);
  void setDAD(word displayAddress); // displayAddress(for multiple VFD);
  void setBitmapOrder(int order);
  //
  // Native Graphic DMA Commands of VFD
  //
  void writeBitImage(word address,  word imagesize, byte *bitmap);
  void writeAreaBitImage(word address, word xbyte, word ybyte, byte *bitmap);
  void setDisplayStartAddress(word address);
  void syncNextCommand();
  void setBrightness(byte brightness);
  //
  // Operation to VFD Display Address and drawing address
  //
  void setDrawingAddress(word address);
  void rotateDrawingAddress();
  void setDisplayStartAddressToDrawingAddress(); // set start_addr = draw_addr
  //
  // FrameBuffer and VFD interaction
  //
  void clear();
  void clearFrameBuffer();
  void show();
  void rotateAndShow();
  void syncAndShow();
  void syncRotateAndShow();
  void showAllArea();
private:
  //
  byte *m_buf = NULL;
  bool m_first_show;
  word m_disp_memsize;
  word m_disp_areasize;
  word m_drawing_addr;
  //
  void flushCommandData();
  void writeCommand(byte command);
  // DAD(Display Address for using multiple VFD modules)
  word m_dad;
};

typedef GU3000Graphic VFD;

#endif
