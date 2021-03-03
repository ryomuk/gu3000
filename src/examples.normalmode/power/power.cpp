#include <string.h>
#include "gu3000normal.h"

void usage(){
  fprintf(stderr, "usage: power {on | off}\n");
  exit(1);
}

int main(int argc, char *argv[]){
  int powerMode;
  VFD vfd;

  if(argc == 1){
    usage();
  }
  
  if(strcmp(argv[1], "on") == 0){
    powerMode = VFD_DISPLAY_POWER_ON;
  } else if(strcmp(argv[1], "off") == 0){
    powerMode = VFD_DISPLAY_POWER_OFF;
  } else {
    usage();
  }

  vfd.powerMode(powerMode);
}
