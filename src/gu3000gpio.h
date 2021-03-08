#ifndef GU3000GPIO_H
#define GU3000GPIO_H

// gu3000gpio.h
//
// Header file for GU3000GPIO class
// commonly used in both graphic DMA mode (gu3000graphic.cpp)
// and normal command mode (gu3000normal.cpp)

#include "gu3000common.h"
//
// GPIO configuration (wiringPi numbering)
//
#define VFD_RDY   18                // <- VFD
#define VFD_WR    19                // -> VFD (Active Low)
#define VFD_Data0 20                // -> VFD

// see software manual Sec.5.3 "Protocol"
#define VFD_DAD_BROADCAST    0xff // Broadcast Address

//
// Bit Order of Image Data for writeByteImage()
//
#define VFD_MSBFIRST 0
#define VFD_LSBFIRST 1
#define VFD_DEFAULT_BITMAPORDER VFD_LSBFIRST

#define VFD_TIMEOUT_RDY 2000 // ms

//
// Class for Parallel Interface
//
class GU3000GPIO{
public:
  GU3000GPIO(){
    init();
  };
  void init();
  void init(int rdy, int wr,
	    int d0, int d1, int d2, int d3,
	    int d4, int d5, int d6, int d7); 
  void setBitmapOrder(int order);
protected:
  inline void waitRDY();
  void writeByte(byte b);
  void writeByteImage(byte b);
  void writeWord(word w);
private:
  // hardware settings
  int m_rdy; // GPIO pinnumber
  int m_wr;  // GPIO pinnumber
  int m_d0, m_d1, m_d2, m_d3, m_d4, m_d5, m_d6, m_d7;  // GPIO pinnumber
  int m_bitmapOrder; // Bit Order of Image Data
};

#endif
