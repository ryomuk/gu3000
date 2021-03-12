#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
//
//  Header file for FrameBuffer class
//

typedef unsigned char byte;
typedef unsigned short word;

#include "font.h"

#define bit(x) (1<<(x))
#define min(x, y) ((x) <= (y) ? (x): (y))
#define max(x, y) ((x) >= (y) ? (x): (y))

// Spacing of tab stops for write('\t')
#define FRAMEBUFFER_DEFAULT_TABSTOP 8

class FrameBuffer{
public:
  FrameBuffer(){};
  FrameBuffer(int x, int y){
    init(x, y);
  };
  byte *buf = NULL;
  int WIDTH;
  int HEIGHT;
  int bufsize; // = WIDTH * HEIGHT / 8
  int cursor_x;
  int cursor_y;
  Font *font;
  Font **fontList;
  //
  // basic mehods
  //
  void init(int width, int height);
  //
  void fill(byte c);
  void clear();
  //
  // methods for  drawing graphics
  //
  inline void pset(int x, int y){ // fast but without parameter domain check
    buf[x*m_ybytes + (y / 8)] |= bit(y & 7);
  };
  inline void preset(int x, int y){ // fast but without parameter domain check
    buf[x*m_ybytes + (y / 8)] &= ~bit(y & 7);
  };
  int getPixel(int x, int y);
  int getPixelMSBfirst(int x, int y);
  void drawPixel(int x, int y, int pen);
  void drawLine(int x0, int y0, int x1, int y1, int pen);
  void drawBox(int x0, int y0, int x1, int y1, int pen);
  void drawBoxFill(int x0, int y0, int x1, int y1, int pen);
  void drawBitmap(int x, int y, const byte *bitmap, int width, int height);
  //
  // methods for drawing characters
  //
  void putchar(int c);
  void puts(const char *s);
  void drawChar(int x, int y, byte c);
  void setCursor(int x, int y);
  void scrollByte();
  void setTabstop(int n);
  //
  // methods for fonts
  //
  void setFont(Font *font);
  void setFontByName(const char *fontname);
  Font *getFontByName(const char *fontname);
  void setFontDefault(); // set font to default font
  void setFontProportional();
  void setFontFixedWidth();
  void invertFontBitmapOrder(); // for use with setBitmapOrder(VFD_MSBFIRST)
  //
  // methods for mapping different format bitmaps
  //
  void loadBitmapHLSB(byte *bmp, int width, int height);
  void loadBitmapBMP(byte *bmp, int width, int height);
  void loadBitmapBytePerPixel(byte *bmp, int width, int height);
private:
  int m_ybytes; // = HEIGHT / 8
  //
  // for grahpics
  //
  void writeLine(int x0, int y0, int x1, int y1, int pen);
  void writeFastVline(int x, int y, int vlength, int pen);
  void writeFastHline(int x, int y, int hlength, int pen);
  //
  // for font and characters
  //
  int m_tabstop;
  //
  byte *m_font_bitmap;
  int m_font_width;
  int m_font_height;
  int m_font_xspace;
  int m_font_yspace;
  byte m_font_firstcode;
  byte m_font_lastcode;
  //
  int m_font_num_chars;
  int m_font_bytes;
  //
  // for proportional font
  //
  int m_font_proportional = false;
  const byte **m_pfont_bitmap_ptr = NULL;
  const byte *bitmapContentTop(const byte *bitmap, int width, int height);
  int *m_pfont_width = NULL;
  int bitmapContentWidth(const byte *bitmap, int width, int height);
};


#endif
