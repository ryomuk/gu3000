// Parallel Interface for
// Raspberry Pi GPIO and Noritake Itron GU-3000 Series VFD

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h> // for clock_gettime()
#include "gu3000gpio.h"

void GU3000GPIO::init(){
  init(VFD_RDY, VFD_WR,
       VFD_Data0, VFD_Data0+1, VFD_Data0+2, VFD_Data0+3,
       VFD_Data0+4, VFD_Data0+5, VFD_Data0+6, VFD_Data0+7);
}

void GU3000GPIO::init(int rdy, int wr,
		     int d0, int d1, int d2, int d3,
		     int d4, int d5, int d6, int d7){
  m_rdy = rdy;
  m_wr  = wr;
  m_d0  = d0;
  m_d1  = d1;
  m_d2  = d2;
  m_d3  = d3;
  m_d4  = d4;
  m_d5  = d5;
  m_d6  = d6;
  m_d7  = d7;

  // Initialize WiringPi
  wiringPiSetupGpio();

  pinMode(m_rdy, INPUT);

  pinMode(m_d0, OUTPUT);
  pinMode(m_d1, OUTPUT);
  pinMode(m_d2, OUTPUT);
  pinMode(m_d3, OUTPUT);
  pinMode(m_d4, OUTPUT);
  pinMode(m_d5, OUTPUT);
  pinMode(m_d6, OUTPUT);
  pinMode(m_d7, OUTPUT);
  pinMode(m_wr, OUTPUT);  digitalWrite(m_wr, HIGH); // negate wr(active low)

  setBitmapOrder(VFD_DEFAULT_BITMAPORDER);

#ifndef VFD_DEGUB_IGNORE_RDY
  delayMicroseconds(1000);
  if(!digitalRead(m_rdy)){
    delay(VFD_TIMEOUT_RDY);
    if(!digitalRead(m_rdy)){
      fprintf(stderr, "GU3000::init(): Cannot initialize VFD (RDY timeout)\n");
      exit(1);
    }
  }
#endif
}

inline void GU3000GPIO::waitRDY(){
#ifndef VFD_DEGUB_IGNORE_RDY
  while(!digitalRead(m_rdy)){
    // delayMicroseconds(1);
  }
#endif
}

void delayNanoseconds(unsigned int howLong)
{
  struct timespec tNow, tEnd;

  clock_gettime(CLOCK_MONOTONIC, &tNow);
  tEnd.tv_sec = tNow.tv_sec;
  tEnd.tv_nsec = tNow.tv_nsec + howLong;
  if(tEnd.tv_nsec >= 1000000000L){
    tEnd.tv_sec++;
    tEnd.tv_nsec -= 1000000000L;
  }
  do{
    clock_gettime(CLOCK_MONOTONIC, &tNow);
  } while ( (tNow.tv_sec == tEnd.tv_sec) ?
	    (tNow.tv_nsec < tEnd.tv_nsec)
	    : (tNow.tv_sec < tEnd.tv_sec));
}

void GU3000GPIO::writeByte(byte byteData){
  waitRDY();
  
  digitalWrite(m_wr, LOW); // assert WR(active low)

  // set data
  digitalWrite(m_d0, byteData & bit(0));
  digitalWrite(m_d1, byteData & bit(1));
  digitalWrite(m_d2, byteData & bit(2));
  digitalWrite(m_d3, byteData & bit(3));
  digitalWrite(m_d4, byteData & bit(4));
  digitalWrite(m_d5, byteData & bit(5));
  digitalWrite(m_d6, byteData & bit(6));
  digitalWrite(m_d7, byteData & bit(7));

  digitalWrite(m_wr, HIGH); //negate WR(active low)

  delayMicroseconds(1); //500ns is enough?
  //for(volatile int i = 0; i < 80; i++){};
}

void GU3000GPIO::setBitmapOrder(int order){
  m_bitmapOrder = order;
}

void GU3000GPIO::writeByteImage(byte byteData){
  waitRDY();

  digitalWrite(m_wr, LOW); // assert WR(active low)

  //  VFD hardware pixel mapping is MSB first (why??)
  //  See software manual (section 5.2(page 63))
  //       x
  // y     0 1 2 3 4 5... 255
  // 0  D7
  //    D6
  //    D5
  //    D4
  //    D3
  //    D2
  //    D1
  //    D0
  // 1  D7
  //    D6
  //    D5
  //    D4
  //    .
  //    .

  // set data
  if(m_bitmapOrder == VFD_MSBFIRST){
    digitalWrite(m_d7, byteData & bit(7));
    digitalWrite(m_d6, byteData & bit(6));
    digitalWrite(m_d5, byteData & bit(5));
    digitalWrite(m_d4, byteData & bit(4));
    digitalWrite(m_d3, byteData & bit(3));
    digitalWrite(m_d2, byteData & bit(2));
    digitalWrite(m_d1, byteData & bit(1));
    digitalWrite(m_d0, byteData & bit(0));
  } else {
    digitalWrite(m_d7, byteData & bit(0));
    digitalWrite(m_d6, byteData & bit(1));
    digitalWrite(m_d5, byteData & bit(2));
    digitalWrite(m_d4, byteData & bit(3));
    digitalWrite(m_d3, byteData & bit(4));
    digitalWrite(m_d2, byteData & bit(5));
    digitalWrite(m_d1, byteData & bit(6));
    digitalWrite(m_d0, byteData & bit(7));
  }
  digitalWrite(m_wr, HIGH); //negate WR(active low)

  //delayNanoseconds(500);
  delayMicroseconds(1); //500ns is enough?
  //for(volatile int i = 0; i < 80; i++){};
}

void GU3000GPIO::writeWord(word wordData){
  writeByte((byte)(wordData & 0xff)); // Lower Byte
  writeByte((byte)(wordData >> 8));   // Higher Byte
}
