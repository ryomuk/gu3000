#ifndef FONT_H
#define FONT_H

typedef unsigned char byte;

// Data Structure of Fonts
//
typedef struct {
  const byte *bitmap; // VLSB bitmap
  const char *name;   // for {set/get}FontByName()
  int width;
  int height;
  int xspace;
  int yspace;
  byte firstcode;
  byte lastcode;
} Font;

extern Font *g_DefaultFont;
extern Font *g_FontList[];

// width of the ' '(space char) in proportional font
//
#define FONT_WIDTH_OF_PROPORTIONAL_SPACECHAR 1

#endif
