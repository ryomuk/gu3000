#include <stdio.h>
#include <stdlib.h>
#include <gu3000graphic.h>

// The raw image data from ffmpeg -c:v rawvideo is MSB first,
// so settting GU3000PIO::writeByteImage() to MSB first mode
// is a little bit faster

#define MSBFIRST
//#define LSBFIRST

#ifdef LSBFIRST
inline byte swapbit8(byte x){
  byte y;
  y =  (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);  y <<= 1;  x >>= 1;
  y |= (x & 1);
  return(y);
}
#endif //LSBFIRST

int main(int argc, char *argv[]){
  FILE *fp = stdin;
  VFD vfd;
  char linebuf[1024];
  int n;
  unsigned long time_s;
  unsigned long time_lastloop = 0;
  
#ifdef MSBFIRST
  vfd.setBitmapOrder(VFD_MSBFIRST);
  vfd.invertFontBitmapOrder();
#endif
  
  if(argc > 1){
    if((fp = fopen(argv[1], "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], argv[1]);
      exit(1);
    }
  }
  
  while(1){
    time_s = micros();
    if(fread(vfd.buf, sizeof(byte), vfd.bufsize, fp) == 0){
      exit(0);
    }
#ifdef LSBFIRST
    for(int i = 0; i < vfd.bufsize; i++){
      vfd.buf[i] = swapbit8(vfd.buf[i]);
    }
#endif    
    sprintf(linebuf, "%dusec(%dFPS)\n%d",
	    (int)(time_lastloop),
	    time_lastloop ? (int)(1000000.0/time_lastloop): 0,
	    n++
	    );
    vfd.setCursor(0, 0);
    vfd.puts(linebuf);
    vfd.show();
    time_lastloop = micros() - time_s;
  }
}
