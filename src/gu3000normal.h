#ifndef GU3000_NORMAL_H
#define GU3000_NORMAL_H

#include "gu3000gpio.h"
#include "framebuffer.h"

//
//   Normal Command Mode
//
#define GU3000_NORMALMODE

#define VFD_SCROLLMODE_OVERWRITE     0x01
#define VFD_SCROLLMODE_VERTICAL      0x02
#define VFD_SCROLLMODE_HORIZONTAL    0x03
#define VFD_SCROLLMODE_HORIZONTAL_ON 0x05

#define CODE_BackSpace      0x08
#define CODE_HorizontalTab  0x09
#define CODE_LineFeed       0x0a
#define CODE_HomePosition   0x0b
#define CODE_CarriageReturn 0x0d
#define CODE_DisplayClear   0x0c
#define CODE_LineClear      0x18
#define CODE_LineEndClear   0x19

#define VFD_DISPLAY_POWER_OFF      0x00
#define VFD_DISPLAY_POWER_ON       0x01
#define VFD_DISPLAY_AUTO_POWER_OFF 0x10

class GU3000Normal : private GU3000GPIO, public FrameBuffer {
 public:
  //
  GU3000Normal(){
    init();
  };
  // Geometry of Visible Area
  int xsize;
  int ysize;
  void init(){
    init(VFD_Xdots, VFD_Ydots, VFD_DispMemSize);
  };
  void init(int x, int y, int memsize);
  // Normal mode commands
  void initialize();
  void setBrightness(byte b);
  void setCursorMode(byte b);
  void setCursor(word x, word y);
  void setScrollMode(byte b);
  void putchar(int c);
  void drawDot(int x, int y, int pen);
  void drawLineBox(int x1, int y1, int x2, int y2, int pen, int mode);
  void drawLine(int x1, int y1, int x2, int y2, int pen);
  void drawBox(int x1, int y1, int x2, int y2, int pen);
  void drawBoxFill(int x1, int y1, int x2, int y2, int pen);
  void deleteFillBox(int x1, int y1, int x2, int y2, int pen);
  void powerMode(byte p);
  void autoPowerOff(byte t);
  //
  // for compatibility with graphic DMA mode
  //
  void pset(int x, int y){ drawDot(x, y, 1); };
  void preset(int x, int y){ drawDot(x, y, 0); };
  void writeBitImage(word startAddress, word size, byte *imagedata);
  void fillBuffer(word startAddress, byte writeData);
  void show(){};
  void rotateAndShow(){};
  void syncAndShow(){};
  void syncRotateAndShow(){};
  void clearDisplay();
  void clearFrameBuffer();
  void puts(char *c);
private:
  int m_ybytes;
  int m_disp_areasize;
};

typedef GU3000Normal VFD;

#endif
