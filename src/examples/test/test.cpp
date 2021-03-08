#include <stdio.h>
#include <gu3000graphic.h>

#define LOOPS 100

void test_dotfill(VFD vfd)
{
  int x, y;
  for(int j = 0; j < LOOPS; j++){
    for(x = 0; x < vfd.WIDTH; x++){
      for(y = 0; y < vfd.HEIGHT; y++){
	vfd.pset(x, y);
      }
    }
  }
}

void test_vline(VFD vfd, int pen){
  int i;
  int midYdot = vfd.HEIGHT/2;

  for(int j = 0; j < LOOPS; j++){
    for(i = 0; i < vfd.WIDTH; i+=2){
      vfd.drawLine(i, midYdot-i/4, i, midYdot+i/4, pen);
    }
  }
}

void test_hline(VFD vfd, int pen){
  int i;
  int midXdot = vfd.WIDTH/2;

  for(int j = 0; j < LOOPS; j++){
    for(i = 0; i < vfd.HEIGHT; i+=2){
      vfd.drawLine(midXdot-i, i, midXdot+i, i, pen);
    }
  }
}

void test_box(VFD vfd, int pen){
  int i;
  int midXdot = vfd.WIDTH/2;
  int midYdot = vfd.HEIGHT/2;

  for(int j = 0; j < LOOPS; j++){
    for(i = 0; i < vfd.WIDTH; i+=8){
      vfd.drawBox(i, midYdot-i/4, i+5, midYdot+i/4, pen);
    }
    for(i = 0; i < vfd.HEIGHT; i+=8){
      vfd.drawBox(midXdot-i, i, midXdot+i, i+7, pen);
    }
  }
}

void test_boxfill(VFD vfd, int pen){
  int i;
  int midXdot = vfd.WIDTH/2;
  int midYdot = vfd.HEIGHT/2;

  for(int j = 0; j < LOOPS; j++){
    for(i = 0; i < vfd.WIDTH; i+=8){
      vfd.drawBoxFill(i, midYdot-i/4, i+5, midYdot+i/4, pen);
    }
    for(i = 0; i < vfd.HEIGHT; i+=8){
      vfd.drawBoxFill(midXdot-i, i, midXdot+i, i+7, pen);
    }
  }
}

void test_line(VFD vfd)
{
  int x;
  int maxXdot = vfd.WIDTH-1;
  int maxYdot = vfd.HEIGHT-1;

  for(int j = 0; j < LOOPS; j++){
    for(x = 0; x < vfd.WIDTH; x+=7){
      vfd.drawLine(0,              0, x, maxYdot, 1);
      vfd.drawLine(0,        maxYdot, x,       0, 1);
      vfd.drawLine(maxXdot,        0, x, maxYdot, 1);
      vfd.drawLine(maxXdot,  maxYdot, x,       0, 1);
    }
  }
}

void test_putchar(VFD vfd)
{
  for(int j = 0; j < LOOPS; j++){
    for(int i = 0; i < 672; i++){
      char c;
      c = (i & 0x5f) + 0x20;
      vfd.putchar(c); // 400us/char
    }
  }
}

void pause(){
  delay(1000);
  //getchar();
}
int main(void){
  VFD vfd;
  unsigned long t_start, t_elapsed;

#define measure(function)\
  t_start = micros();\
  function;\
  t_elapsed = micros() - t_start;\
  printf("%32s: %6dus\n", #function, (int)t_elapsed);

#define show_and_pause(x) measure(vfd.show()); pause();

  printf("LOOPS(in test_xxx())=%d\n", LOOPS);
  
  measure(vfd.clear());
  show_and_pause();

  measure(test_dotfill(vfd));
  show_and_pause();

  vfd.clear();
  measure(test_box(vfd, 1));
  show_and_pause();

    measure(test_boxfill(vfd, 1));
  show_and_pause();

  vfd.clear();
  measure(test_vline(vfd, 1));
  show_and_pause();
  measure(test_hline(vfd, 1));
  show_and_pause();
  measure(vfd.fill(0xff));
  show_and_pause();
  measure(test_vline(vfd, 0));
  show_and_pause();
  measure(test_hline(vfd, 0));
  show_and_pause();

  vfd.clear();
  measure(test_line(vfd));
  show_and_pause();

  measure(test_putchar(vfd));
  show_and_pause();
  vfd.clear();
  vfd.setCursor(vfd.xsize/2, vfd.ysize/2);
  measure(vfd.putchar('A'));
  show_and_pause();
  measure(vfd.showAllArea());
  vfd.setCursor(vfd.xsize/2, vfd.ysize/2);
  measure(vfd.puts("Hello World!"));
  show_and_pause();


  // vfd.drawLine(0, 0, VFD_Max_Xdot, VFD_Max_Ydot); // 8900us
  // vfd.drawLine(0, 0, 0, 0); // 8900us
  // vfd.rawBox(0, 0, VFD_Max_Xdot, VFD_Max_Ydot); //  8700us
  // vfd.fillBox(0, 0, VFD_Max_Xdot, VFD_Max_Ydot); // 9000us
  // vfd.pset(VFD_Max_Xdot, VFD_Max_Ydot); //8000us
  
}
