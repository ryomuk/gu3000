#include <stdio.h>
#include <gu3000graphic.h>

void test_dotfill(VFD vfd)
{
  int x, y;
  for(x = 0; x < vfd.WIDTH; x++){
    for(y = 0; y < vfd.HEIGHT; y++){
      vfd.pset(x, y);
    }
  }
  vfd.show();
  
  for(x = 0; x < vfd.WIDTH; x++){
    for(y = 0; y < vfd.HEIGHT; y++){
      vfd.preset(x, y);
    }
  }
  vfd.show();
}

void test_line(VFD vfd)
{
  int x;
  int maxXdot = vfd.WIDTH-1;
  int maxYdot = vfd.HEIGHT-1;

  for(x = 0; x < vfd.WIDTH; x+=4){
    vfd.drawLine(0,              0, x, maxYdot, 1);
    vfd.drawLine(0,        maxYdot, x,       0, 1);
    vfd.drawLine(maxXdot,        0, x, maxYdot, 1);
    vfd.drawLine(maxXdot,  maxYdot, x,       0, 1);
    vfd.show();
  }
  for(x = 0; x < vfd.WIDTH; x+=4){
    vfd.drawLine(0,             0, x, maxYdot, 0);
    vfd.drawLine(0,       maxYdot, x,       0, 0);
    vfd.drawLine(maxXdot,       0, x, maxYdot, 0);
    vfd.drawLine(maxXdot, maxYdot, x,       0, 0);
    vfd.show();
  }
}

int main(void){
  int n = 0;
  unsigned long time_s, time_e;

  VFD vfd;

#if 0
  while(1){
    unsigned long t_start, t_end;
    t_start = micros();
    vfd.rotateAndSetDisplayStartAddress();
    t_end = micros();
    printf("%d us\n", (int)(t_end - t_start));
    getchar();
  }
  
#endif
  while(1){
    test_dotfill(vfd);

    test_line(vfd);
    vfd.show();
    delay(1000);
    
    for(int i = 0; i < 10; i++){
      char c;
      c = (i&0xf)+0x30;
      vfd.putchar(c); // (11us-)150us(-30000us)
    }
    vfd.show();
    
    time_s = micros();
    // vfd.drawLine(0, 0, VFD_Max_Xdot, VFD_Max_Ydot); // 8900us
    // vfd.drawLine(0, 0, 0, 0); // 8900us
    // vfd.rawBox(0, 0, VFD_Max_Xdot, VFD_Max_Ydot); //  8700us
    // vfd.fillBox(0, 0, VFD_Max_Xdot, VFD_Max_Ydot); // 9000us
    // vfd.pset(VFD_Max_Xdot, VFD_Max_Ydot); //8000us
    for(int i = 0; i < 660; i++){
      char c;
      c = (i&0xf)+0x30;
      vfd.putchar(c); // 400us/char
    }
    vfd.show();

    time_e = micros();
    if(n == 0){
      printf("%d usec, %dFPS\n",
	     (int)(time_e - time_s),
	     (int)(1000000.0/(time_e - time_s)));
    }
    //    n++; n &= 0xff;
  }

}
