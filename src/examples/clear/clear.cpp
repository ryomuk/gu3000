#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gu3000graphic.h>

int main(int argc, char *argv[]){
  VFD vfd;
  int c = 0;
  int brightness = VFD_BRIGHTNESS_MID;

  if(argc > 1){
    if(strncmp(argv[1], "0b", 2) == 0){
      c = strtol(&argv[1][2], NULL, 2);
    } else if(strncmp(argv[1], "0x", 2) == 0){
      c = strtol(argv[1], NULL, 16);
    } else {
      c = atoi(argv[1]);
    }
  }
  if(argc > 2){
    brightness = atoi(argv[2]);
  }
  if( c < 0 || c > 255 || brightness < 0 || brightness > 24){
    fprintf(stderr,
	    "usage: clear [value(0..255)] [brightness(0..4 or 16..24]\n");
    exit(1);
  }
  
  vfd.setBrightness(brightness);
  vfd.fill(c);
  vfd.show();
}
