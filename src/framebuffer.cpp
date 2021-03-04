//
// Frame Buffer
//
// Upper Left is (0,0)
// Buffer address increments Vertical direction(Upper to Lower)
// Pixel mapping is LSB first (most upper is LSB, most lower is MSB)
// 1bit/1pixel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "framebuffer.h"

void FrameBuffer::init(int x, int y){
  WIDTH = x;
  HEIGHT = y;

  m_ybytes = HEIGHT / 8;
  if(HEIGHT & 7){
    m_ybytes++;
  }
  bufsize = WIDTH * m_ybytes;
  if(buf != NULL){
    free(buf);
  }
  if((buf = (byte *)malloc(bufsize)) == NULL){
    fprintf(stderr, "Cannot malloc in FrameBuffer\n");
    exit(1);
  }

  clear(); // fill buffer with 0 and set cursor to (0,0)
  fontList = g_FontList;
  setFont(g_DefaultFont);
  setFontFixedWidth();
  setTabstop(FRAMEBUFFER_DEFAULT_TABSTOP);
}

void FrameBuffer::setCursor(int x, int y){
  cursor_x = x;
  cursor_y = y;
}

int FrameBuffer::getPixel(int x, int y){
  int memoffset;
  byte bitpattern;
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT){
    return(0);
  }
  memoffset = x*m_ybytes + (y / 8);
  bitpattern = bit(y & 7);
  return(buf[memoffset] & bitpattern);
}

int FrameBuffer::getPixelMSBfirst(int x, int y){
  int memoffset;
  byte bitpattern;
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT){
    return(0);
  }
  memoffset = x*m_ybytes + (y / 8);
  bitpattern = bit(7-(y & 7));
  return(buf[memoffset] & bitpattern);
}

void FrameBuffer::drawPixel(int x, int y, int pen){
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
  if(pen){
    pset(x, y);
  } else {
    preset(x, y);
  }
}

void FrameBuffer::writeLine(int x0, int y0, int x1, int y1, int pen){
  int dx, dy, sx, sy, a, a1, e;
        
  if(x0 <= x1){
    dx = x1 - x0;
    sx = 1;
  } else {
    dx = x0 - x1;
    sx = -1;
  }
  if(y0 <= y1){
    dy = y1 - y0;
    sy = 1;
  } else {
    dy = y0 - y1;
    sy = -1;
  }
  if(dx >= dy){
    a  = 2 * dy;
    a1 = a - 2 * dx;
    e  = a - dx;
    
    while(1){
      drawPixel(x0, y0, pen);
      if(x0 == x1) break;
      if(e >= 0){
	y0 += sy;
	e += a1;
      } else {
	e += a;
      }
      x0 += sx;
    }
  } else {
    a  = 2 * dx;
    a1 = a - 2 * dy;
    e  = a - dy;
    while(1){
      drawPixel(x0, y0, pen);
      
      if(y0 == y1) break;
      
      if(e >= 0){
	x0 += sx;
	e += a1;
      } else {
	e += a;
      }
      y0 += sy;
    }
  }
}

void FrameBuffer::writeFastVline(int x, int y, int vlength, int pen){
  //  writeLine(x, y, x, y + vlength, pen); // temporary implementation
  //  return;

  int i_start, i_end, i;
  static const byte bitmap1[8] = {0b11111111,
				  0b11111110,
				  0b11111100,
				  0b11111000,
				  0b11110000,
				  0b11100000,
				  0b11000000,
				  0b10000000};
  static const byte bitmap2[8] = {0b00000001,
				  0b00000011,
				  0b00000111,
				  0b00001111,
				  0b00011111,
				  0b00111111,
				  0b01111111,
				  0b11111111};

  if(x < 0 || x >= WIDTH) return;
  if( y < 0){
    vlength = vlength - (-y);
    y = 0;
  };
  if(y + vlength >= HEIGHT){
    vlength = HEIGHT - y - 1;
  }
  
  i_start = x*m_ybytes + (y / 8);
  i_end   = x*m_ybytes + ((y+vlength) / 8);

  if(pen){
    if(i_start == i_end){
      buf[i_start] |= (bitmap1[y&7] & bitmap2[(y+vlength)&7]);
    } else {
      buf[i_start] |= bitmap1[y&7];
      for(i = i_start+1; i < i_end; i++){
	buf[i] = 0xff;
      }
      buf[i_end] |= bitmap2[(y+vlength)&7];
    }
  } else {
    if(i_start == i_end){
      buf[i_start] &= ~(bitmap1[y&7] & bitmap2[(y+vlength)&7]);
    } else {
      buf[i_start] &= ~bitmap1[y&7];
      for(i = i_start+1; i < i_end; i++){
	buf[i] = 0x00;
      }
      buf[i_end] &= ~bitmap2[(y+vlength)&7];
    }
  }
}

void FrameBuffer::writeFastHline(int x, int y, int hlength, int pen){
  //writeLine(x, y, x + hlength, y, pen); // temporary implementation
  //return;
  int i_start, i_end, i;

  byte bitpattern;

  if(y < 0 || y >= HEIGHT) return;
  if( x < 0){
    hlength = hlength - (-x);
    x = 0;
  };
  if(x + hlength >= WIDTH){
    hlength = WIDTH - x - 1;
  }

  i_start = x*m_ybytes + (y / 8);
  i_end   = (x+hlength)*m_ybytes + (y/ 8);
    
  if(pen){
    bitpattern = bit(y&7);
    for(i = i_start; i <= i_end; i+=m_ybytes){
      buf[i] |= bitpattern;
    }
  } else {
    bitpattern = ~bit(y&7);
    for(i = i_start; i <= i_end; i+=m_ybytes){
      buf[i] &= bitpattern;
    }
  }
}


void FrameBuffer::drawBox(int x0, int y0, int x1, int y1, int pen){
  writeLine(x0, y0, x0, y1, pen);
  writeLine(x0, y1, x1, y1, pen);
  writeLine(x1, y1, x1, y0, pen);
  writeLine(x1, y0, x0, y0, pen);
}

void FrameBuffer::drawBoxFill(int x0, int y0, int x1, int y1, int pen){
  int x;
  if(x0 < x1){
    for(x = x0; x <=x1; x++){
      writeLine(x, y0, x, y1, pen);
    }
  } else {
    for(x = x1; x <=x0; x++){
      writeLine(x, y0, x, y1, pen);
    }
  }
}

void FrameBuffer::drawLine(int x0, int y0, int x1, int y1, int pen){
  if(x0 == x1){
    if(y1 > y0){
      writeFastVline(x0, y0, y1 - y0, pen);
    } else {
      writeFastVline(x0, y1, y0 - y1, pen);
    }
  } else if (y0 == y1){
    if(x1 > x0){
      writeFastHline(x0, y0, x1 - x0, pen);
    } else {
      writeFastHline(x1, y0, x0 - x1, pen);
    }
  } else {
    writeLine(x0, y0, x1, y1, pen);
  }
}


void FrameBuffer::fill(byte c){
  for(int i = 0; i < bufsize; i++){
    buf[i] = c;
  }
}

void FrameBuffer::clear(){
  fill(0);
  setCursor(0, 0);
}

void FrameBuffer::setFont(Font *font){
  currentFont = font;

  m_font_bitmap = (byte *)(font->bitmap);
  m_font_width = font->width;
  m_font_height = font->height;
  m_font_xspace = font->xspace;
  m_font_yspace = font->yspace;
  m_font_firstcode = font->firstcode;
  m_font_lastcode = font->lastcode;
  m_font_num_chars = font->lastcode - font->firstcode + 1;
  
  m_font_bytes = font->height / 8;
  if(font->height & 7){
    m_font_bytes++;
  }
  m_font_bytes = m_font_bytes * font->width;

  if(m_font_proportional){
    setFontProportional();
  }
}

void FrameBuffer::setDefaultFont(){
  setFont(g_DefaultFont);
  setFontFixedWidth();
}

Font *FrameBuffer::getFontByName(const char *fontname){
  for(int i = 0; fontList[i] != NULL; i++){
    if(strcmp(fontname, fontList[i]->name) == 0){
      return(fontList[i]);
    }
  }
  return(NULL);
}

void FrameBuffer::setFontByName(const char *name){
  Font *f;
  
  f = getFontByName(name);
  if(f == NULL){
    fprintf(stderr, "FrameBuffer::setFontByName: '%s' not found\n",
	    name);
  } else {
    setFont(f);
  }
}

void FrameBuffer::invertFontBitmapOrder(){
  byte *f = m_font_bitmap;

  m_font_bitmap = (byte *)malloc(m_font_num_chars * m_font_bytes);

  for(int i = 0; i < m_font_num_chars * m_font_bytes; i++){
    m_font_bitmap[i] = swapbit8(f[i]);
  }
}
  
const byte *FrameBuffer::bitmapContentTop(const byte *bitmap,
					  int width, int height){
  int height_bytes;
  byte bits;
  
  height_bytes = height / 8;
  if(height & 7){
    height_bytes++;
  }

  for(int x = 0; x < width; x++){
    bits = 0;
    for(int j = 0; j < height_bytes; j++){
      bits |= bitmap[x*height_bytes + j];
    }
    if(bits){
      return(&(bitmap[x*height_bytes]));
    }
  }
  return(bitmap);
}

int FrameBuffer::bitmapContentWidth(const byte *bitmap, int width, int height){
  int x_top, x_end;
  int height_bytes;
  byte bits;
  
  height_bytes = height / 8;
  if(height & 7){
    height_bytes++;
  }

  x_top = -1;
  x_end = 0;
  for(int x = 0; x < width; x++){
    bits = 0;
    for(int j = 0; j < height_bytes; j++){
      bits |= bitmap[x*height_bytes + j];
    }
    if(bits){
      if(x_top < 0){
	x_top = x;
      }
      x_end = x;
    }
  }
  return(x_end - x_top + 1);
}

void FrameBuffer::setFontFixedWidth(){
  m_font_proportional = false;
  m_font_width = currentFont->width;
  m_font_xspace = currentFont->xspace;
}

void FrameBuffer::setFontProportional(){
  m_font_proportional = true;
  if(m_font_xspace < 1){
    m_font_xspace = 1;
  }
  
  m_pfont_bitmap_ptr =
    (const byte **) realloc(m_pfont_bitmap_ptr,
			   m_font_num_chars * sizeof(const byte *));
  m_pfont_width =
    (int *) realloc(m_pfont_width,  m_font_num_chars * sizeof(int));

  if(m_pfont_bitmap_ptr == NULL){
    fprintf(stderr, "cannot allocate memory for m_pfont_bitmap_ptr\n");
    exit(1);
  }
  if(m_pfont_width == NULL){
    fprintf(stderr, "cannot allocate memory for m_pfont_width\n");
    exit(1);
  }
  for(int i = 0; i < m_font_num_chars; i++){
    m_pfont_bitmap_ptr[i] = bitmapContentTop(&(m_font_bitmap[i*m_font_bytes]),
					     m_font_width, m_font_height);
    
    m_pfont_width[i] = bitmapContentWidth(&(m_font_bitmap[i*m_font_bytes]),
					  m_font_width, m_font_height);
    if(m_pfont_width[i] == 0){
      m_pfont_width[i] = FONT_WIDTH_OF_PROPORTIONAL_SPACECHAR;
    }
  }
}

void FrameBuffer::drawBitmap(int x, int y,
			     const byte *bitmap, int width, int height){
  // Easy implementation
  int memoffset, height_bytes;
  byte bitpattern;
  
  height_bytes = height / 8;
  if(height & 7){
    height_bytes++;
  }
  for(int i = 0; i < width; i++){
    if(i + x < 0 || i + x >= WIDTH) break;
    for(int j = 0; j < height; j++){
      if(j + y < 0 || j + y >= HEIGHT) break;
      memoffset = i*height_bytes + (j / 8);
      bitpattern = bit(j & 7);
      if(bitmap[memoffset] & bitpattern){
 	pset(x+i, y+j);
      } else {
 	preset(x+i, y+j);
      }
    }
  }
}

void FrameBuffer::drawChar(int x, int y, unsigned char c){
  int i = c - m_font_firstcode;
  if(m_font_proportional){
    drawBitmap(x, y, m_pfont_bitmap_ptr[i],
	       m_pfont_width[i],
	       m_font_height);
  } else {
    drawBitmap(x, y,
	       &(m_font_bitmap[i * m_font_bytes]),
	       m_font_width, m_font_height);
  }
}

void FrameBuffer::scrollByte(){
  int i, j;
  for(i = 0; i < WIDTH; i++){
    for(j = 0; j < m_ybytes -1; j++){
      buf[i * m_ybytes + j] = buf[i * m_ybytes + j + 1];
    }
    buf[i * m_ybytes + j] = 0;
  }
}

void FrameBuffer::putchar(int c){
  if(c >= m_font_firstcode && c <= m_font_lastcode){
    // drawable character
    if(m_font_proportional){
      // set proportional font spacing
      m_font_width = m_pfont_width[c - m_font_firstcode];
    }
    // Check space to draw a character
    if(cursor_x + m_font_width > WIDTH){
      cursor_x = 0;
      cursor_y += m_font_height;
      cursor_y += m_font_yspace;
    }
    // scroll
    while(cursor_y + m_font_height > HEIGHT){
      cursor_y -= 8;
      scrollByte();
    }
    // draw a character
    drawChar(cursor_x, cursor_y, c);
    // advance a cursor position
    cursor_x += m_font_width;
    cursor_x += m_font_xspace;
    return;
  }

  // Process control codes
  if(c == '\n'){
    cursor_x = 0;
    cursor_y += (m_font_height + m_font_yspace);
  } else if(c == '\r'){
    cursor_x = 0;
  } else if(c == '\t'){
    // TAB
    int charwidth = currentFont->width + currentFont->xspace;
    cursor_x += (m_tabstop - ((cursor_x/charwidth) % m_tabstop)) * charwidth;
    cursor_x = ((int)(cursor_x / charwidth)) * charwidth;
  }
}

void FrameBuffer::setTabstop(int n){
  if(n > 0){
    m_tabstop = n;
  }
}

void FrameBuffer::puts(const char *s){
  while(*s != 0){
    putchar(*s++);
  }
}

byte FrameBuffer::swapbit8(byte x){
  byte y;
  y =  (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);
  return(y);
}

// load HLSB bitmap to VLSB frame buffer
void FrameBuffer::loadBitmapHLSB(byte *bmp, int width , int height){
  int x, y, i, n;

  byte hbitmask;
  byte vbitmap;
  int bmp_xbytes;
  int width_draw, height_draw;
  
  width_draw = min(WIDTH, width);
  height_draw = min(HEIGHT, height);
  
  bmp_xbytes = width / 8;
  for(x = 0; x < width_draw; x++){
    hbitmask = bit(7-(x &0x7));
    for(y = 0; y < height_draw; y+= 8){
      vbitmap = 0;
      n = min(8, height_draw - y);
      for(i = 0; i < n; i++){
	if(bmp[x/8 + bmp_xbytes * (y+i)] & hbitmask){
	  vbitmap |= bit(i);
	}
      }
      buf[x * m_ybytes + (y/8)] = vbitmap;
    }
  }
} 


// load contents of BMP file(Lower Left is (0,0), HLSB) to VLSB frame buffer
void FrameBuffer::loadBitmapBMP(byte *bmp, int width , int height){
  int x, y, i, n;

  byte hbitmask;
  byte vbitmap;
  int bmp_xbytes;
  int width_draw, height_draw;
  
  width_draw = min(WIDTH, width);
  height_draw = min(HEIGHT, height);
  
  bmp_xbytes = width / 8;
  for(x = 0; x < width_draw; x++){
    hbitmask = bit(7-(x &0x7));
    for(y = 0; y < height_draw; y+= 8){
      vbitmap = 0;
      n = min(8, height_draw - y);
      for(i = 0; i < n; i++){
	if(bmp[x/8 + bmp_xbytes * (height_draw-(y+i)-1)] & hbitmask){
	  vbitmap |= bit(i);
	}
      }
      buf[x * m_ybytes + (y/8)] = vbitmap;
    }
  }
}


//
// load bitmap data(UpperLeft is (0,0), Horizontal, 1byte/pixel)
// (ex. contents of xwd format)
// to VLSB frame buffer(1bit/pixel)
//
void FrameBuffer::loadBitmapBytePerPixel(byte *bmp, int width , int height){
  int x, y, i, n;

  byte vbitmap;
  int width_draw, height_draw;
  
  width_draw = min(WIDTH, width);
  height_draw = min(HEIGHT, height);
  
  for(x = 0; x < width_draw; x++){
    for(y = 0; y < height_draw; y+=8){
      vbitmap = 0;
      n = min(8, height_draw - y);
      for(i = 0; i < n; i++){
	if(bmp[x + width * (y+i)]){
	  vbitmap |= bit(i);
	}
      }
      buf[x * m_ybytes + (y/8)] = vbitmap;
    }
  }
} 
