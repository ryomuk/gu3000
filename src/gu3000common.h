#ifndef GU3000COMMON_H
#define GU3000COMMON_H

#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

typedef unsigned char byte;
typedef unsigned short word;

//#define VFD_DEGUB_IGNORE_RDY // for debug without VFD module

#define bit(x) (1<<(x))
#define min(x, y) ((x) <= (y) ? (x): (y))
#define max(x, y) ((x) >= (y) ? (x): (y))

// specification of GU-3000 series 256x128 model
// (see software manual Sec.3.2 "Display Memory configuration")
#define VFD_Xdots 256
#define VFD_Ydots 128
#define VFD_DispMemSize 0x2000

// Brightness
// (see software manual Sec.5.4.1.5 "Brightness level")
#define VFD_BRIGHTNESS_OFF 0x00
#define VFD_BRIGHTNESS_MIN 0x01
#define VFD_BRIGHTNESS_MID 0x02
#define VFD_BRIGHTNESS_MAX 0x04

#endif
