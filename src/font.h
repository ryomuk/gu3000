#ifndef FONT_H
#define FONT_H

typedef unsigned char byte;

// Data Structure of Fonts
//
typedef struct {
  const byte *bitmap; // VLSB (Vertical direction LSB first bitmap)
  const char *name;   // for FrameBuffer::{set/get}FontByName()
  int width;
  int height;
  int xspace;
  int yspace;
  int firstcode;
  int lastcode;
} Font;

extern Font *g_FontList[];

#define FONT_DEFAULT_FONTNAME "Noritake6x8"

// width of the ' '(space char) in proportional font
//
#define FONT_WIDTH_OF_PROPORTIONAL_SPACECHAR 1

#endif
