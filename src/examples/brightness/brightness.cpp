#include <stdio.h>
#include <stdlib.h>
#include <gu3000graphic.h>

int main(int argc, char *argv[]){
  VFD vfd;
  int brightness = -1;

  if(argc > 1){
    brightness = atoi(argv[1]);
  }
  if( brightness < 0 || brightness > 24){
    fprintf(stderr,
	    "usage: brightness value(0..4 or 16..24]\n");
    exit(1);
  }
  vfd.setBrightness(brightness);
}
