#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep
#include <gu3000graphic.h>

// The raw image data from ffmpeg -c:v rawvideo is MSB first,
// so settting GU3000PIO::writeByteImage() to MSB first mode
// is a little bit faster

//#define DEFAULT_FPS 29.97
#define DEFAULT_FPS 30.0

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

void usage(){
  fprintf(stderr, "Usage: playbmp [OPTION]... [FILE]\n");
  fprintf(stderr, "  -fps FPS: set FPS\n");
  fprintf(stderr, "  -v, -info: show frame info\n");
  fprintf(stderr, "  -: FILE=stdin\n");
  exit(0);
}
  int main(int argc, char *argv[]){
  FILE *fp = stdin;
  const char *filename = NULL;
  VFD vfd;
  char linebuf[1024];
  int n;
  unsigned long time_s;
  unsigned long time_elapsed = 0;

  bool showinfo = false;
  double fps = DEFAULT_FPS;
  useconds_t looptime, usleeptime;
  
#ifdef MSBFIRST
  vfd.setBitmapOrder(VFD_MSBFIRST);
  vfd.invertFontBitmapOrder();
#endif
  
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      if(strcmp(argv[i], "-fps") == 0){
	i++;
	if(i >= argc) usage();
	fps = atof(argv[i]);
	if(fps <= 0) usage();
      } else if(strcmp(argv[i], "-") == 0){
	fp = stdin;
      } else if( strcmp(argv[i], "-showinfo") == 0 ||
		 strcmp(argv[i], "-v") == 0){
	showinfo = true;
      } else {
	usage();
      }
    } else {
      if(filename == NULL){
	filename = argv[i];
      } else {
	usage();
      }
    }
  }
  if( filename != NULL ){
    if((fp = fopen(filename, "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], filename);
      exit(1);
    }
  }

  
  looptime = 1000000.0 / fps;
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
    if(showinfo){
      sprintf(linebuf, "%dusec(fps=%.0f)\n%d",
	      (int)(time_elapsed),
	      time_elapsed ? (double)(1000000.0/time_elapsed): 0,
	      n++
	      );
      vfd.setCursor(0, 0);
      vfd.puts(linebuf);
    }
    vfd.show();

    time_elapsed = micros() - time_s;
    if( looptime > time_elapsed + 85){
      usleeptime = looptime - time_elapsed - 85;
      usleep(usleeptime);
    }
    time_elapsed = micros() - time_s;
  }
}
