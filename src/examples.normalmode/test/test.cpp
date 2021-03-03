#include <stdio.h>
#include <wiringPi.h>
#include "gu3000normal.h"

void test_dotfill(VFD vfd)
{
  int x, y;
  for(x = 0; x < VFD_Xdots; x++){
    for(y = 0; y < VFD_Ydots; y++){
      vfd.pset(x, y);
    }
  }
  for(x = 0; x < VFD_Xdots; x++){
    for(y = 0; y < VFD_Ydots; y++){
      vfd.preset(x, y);
    }
  }
}

void test_line(VFD vfd)
{
  int x;
  int maxXdot = vfd.xsize-1;
  int maxYdot = vfd.ysize-1;

  for(x = 0; x < vfd.xsize; x+=4){
    vfd.drawLine(0,              0, x, maxYdot, 1);
    vfd.drawLine(0,        maxYdot, x,       0, 1);
    vfd.drawLine(maxXdot,        0, x, maxYdot, 1);
    vfd.drawLine(maxXdot,  maxYdot, x,       0, 1);
    //vfd.show();
  }
  for(x = 0; x < vfd.xsize; x+=4){
    vfd.drawLine(0,             0, x, maxYdot, 0);
    vfd.drawLine(0,       maxYdot, x,       0, 0);
    vfd.drawLine(maxXdot,       0, x, maxYdot, 0);
    vfd.drawLine(maxXdot, maxYdot, x,       0, 0);
    //vfd.show();
  }
}

int main(void){
  int n;
  unsigned long time_s, time_e;

  VFD vfd;

  vfd.initialize();
  vfd.setBrightness(VFD_BRIGHTNESS_MID);
  vfd.setCursorMode(0); // 0:off, 1:on
  vfd.setCursor(0, 0);
  
  // Scroll mode
  vfd.setScrollMode(VFD_SCROLLMODE_VERTICAL);
  //vfd.setScrollMode(VFD_SCROLLMODE_OVERWRITE);

  n = 0;
  vfd.putchar(CODE_DisplayClear);
  while(1){
    //test_dotfill(vfd);
    test_line(vfd);

    for(int i = 0; i < 10; i++){
      char c;
      c = (i&0xf)+0x30;
      vfd.putchar(c); // (11us-)150us(-30000us)
    }

    time_s = micros();
    // vfd.drawLine(0, 0, VFD_Xdots-1, VFD_Ydots-1); // 8900us
    // vfd.drawLine(0, 0, 0, 0); // 8900us
    // vfd.rawBox(0, 0, VFD_Xdots-1, VFD_Ydots-1); //  8700us
    // vfd.fillBox(0, 0, VFD_Xdots-1, VFD_Ydots-1); // 9000us
    // vfd.pset(VFD_Xdots-1, VFD_Ydots-1); //8000us
    for(int i = 0; i < 660; i++){
      char c;
      c = (i&0xf)+0x30;
      vfd.putchar(c); // 400us/char
    }
    time_e = micros();
    if(n == 0){
      printf("%d usec, %dFPS\n",
	     (int)(time_e - time_s),
	     (int)(1000000.0/(time_e - time_s)));
    }
    //    n++; n &= 0xff;
  }

}
