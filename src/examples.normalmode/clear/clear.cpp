#include <stdio.h>
#include <stdlib.h>
#include <gu3000normal.h>

int main(int argc, char *argv[]){
  VFD vfd;
  int c = 0;
  int brightness = VFD_BRIGHTNESS_MID;

  if(argc > 1){
    c = atoi(argv[1]);
  }
  if(argc > 2){
    brightness = atoi(argv[2]);
  }
  if( c < 0 || c > 255 || brightness < 0){
    fprintf(stderr,
	    "usage: clear [code(0..255)] [brightness(0..4 or 16..24]\n");
    exit(1);
  }
  
  vfd.initialize();
  vfd.setBrightness(brightness);
  vfd.fillBuffer(0, c);
}
