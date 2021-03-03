#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep
#include <gu3000graphic.h>

#define DEFAULT_FILENAME "/dev/fb0"
#define DEFAULT_WIDTH 256
#define DEFAULT_HEIGHT 128
#define DEFAULT_BPP 16
#define DEFAULT_FPS 20
#define DEFAULT_DITHER true

void usage(){
  fprintf(stderr, "Usage: showfb [OPTION]... [FILE]\n");
  fprintf(stderr, "  -w[idth] width: set fb width\n");
  fprintf(stderr, "  -h[eight] height: set fb height\n");
  fprintf(stderr, "  -s[cale] scale: set scaling\n");
  fprintf(stderr, "  -bpp: bit per pixel (8, 16, 24, 32...)\n");
  fprintf(stderr, "  -fps FPS: set FPS\n");
  fprintf(stderr, "  -gray: pseudo gray scale with dither\n");
  fprintf(stderr, "  -bw: no dither\n");
  fprintf(stderr, "  -showinfo: show information\n");
  fprintf(stderr, "  -: FILE=stdin\n");
  fprintf(stderr, "Defaults:\n");
  fprintf(stderr, "  filename=%s, w*h*bpp=%dx%dx%d, FPS=%d\n",
	  DEFAULT_FILENAME,
	  DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_BPP, DEFAULT_FPS);
  exit(1);
}

int main(int argc, char *argv[]){
  unsigned long time_s = 0;
  unsigned long time_elapsed;
  
  VFD vfd;
  FILE *fp = NULL;
  const char *filename = DEFAULT_FILENAME ;

  byte *buf = NULL;
  int bufsize;
  int width = DEFAULT_WIDTH;
  int height = DEFAULT_HEIGHT;
  int scale = 1;
  int bit_per_pixel = DEFAULT_BPP;
  int byte_per_pixel;
  int fps = DEFAULT_FPS;
  useconds_t looptime, usleeptime;
  int cnt = 0;
  bool showinfo = false;
  bool dither = DEFAULT_DITHER;
  
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      /*  */ if(strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-width") == 0){
	i++;
	if(i >= argc) usage();
	width = atoi(argv[i]);
      } else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-height") == 0){
	i++;
	if(i >= argc) usage();
	height = atoi(argv[i]);
      } else if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-scale") == 0){
	i++;
	if(i >= argc) usage();
	scale = atoi(argv[i]);
      } else if(strcmp(argv[i], "-bpp") == 0){
	i++;
	if(i >= argc) usage();
	bit_per_pixel = atoi(argv[i]);
      } else if(strcmp(argv[i], "-fps") == 0){
	i++;
	if(i >= argc) usage();
	fps = atoi(argv[i]);
	if(fps <= 0) usage();
      } else if(strcmp(argv[i], "-") == 0){
	fp = stdin;
      } else if(strcmp(argv[i], "-gray") == 0){
	dither = true;
      } else if(strcmp(argv[i], "-bw") == 0){
	dither = false;
      } else if(strcmp(argv[i], "-showinfo") == 0){
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
  if( fp == NULL ){
    if((fp = fopen(filename, "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], filename);
      exit(1);
    }
  }

  looptime = 1000000 / fps;
  
  byte_per_pixel = bit_per_pixel / 8;
  bufsize = width * height * byte_per_pixel;

  if((buf = (byte *)malloc(bufsize)) == NULL){
    fprintf(stderr, "malloc() failed.\n");
    exit(1);
  }
  // ad55 = 10101 101010 10101
  // 0540 = 00000 101010 00000
  if( showinfo ){
    printf("fb='%s', widthxheightxbpp=%dx%dx%d, FPS=%d\n",
	   filename, width, height, bit_per_pixel, fps);
  }
  while(true){
    time_s = micros();
    cnt++;
    fread(buf, sizeof(byte), bufsize, fp);
    
    if( byte_per_pixel > 1){
      for(int i = 0; i < width * height; i++){
	if(byte_per_pixel == 2){ // RGB565(R=0xf800, G=0x07e0, B=0x001f)
	  word *wbuf = (word *)buf;
	  byte red = (byte)(wbuf[i] >> 11) ;
	  byte green = (byte)((wbuf[i] & 0x07e0) >> 5);
	  byte blue = (byte)(wbuf[i] & 0x001f);
	  double y, threshold;
	  bool is_special_color = false;

	  y = 0.299/31 * red + 0.587/63 * green + 0.114/31* blue;

	  if(dither){
	    //	    if((cnt % 2 ) == 0){
	    if(((i/width) % 2) == 0){
	      if(i % 2 == 0){
		threshold = 0.671; // y(10101,101010,10101) = 0.6711
	      } else {
		//threshold = 0.270; // y(11100, 0, 0) = 0.270
		threshold = 0.2025; // y(10101, 0, 0) = 0.2025
	      }
	    } else {
	      if(i % 2 == 0){
		//threshold = 0.102;  // y(0, 0, 11100) = 0.102
		threshold = 0.0772;  // y(0, 0, 10101) = 0.07725
	      } else {
		//threshold = 0.521; // y(0, 111000, 0) = 0.5217
		threshold = 0.3913; // y(0, 101010, 0) = 0.39133
	      }
	    }
	  } else {
	    threshold = 0.670;
	    is_special_color =
	      (wbuf[i] == 0x0540)   // (0, 101010, 0) boot message "[OK]"
	      || (wbuf[i] == 0x52bf) // command line prompt
	      //	     || ((wbuf[i] & 0xf800) == 0xf800) // full R
	      //	     || ((wbuf[i] & 0x07e0) == 0x07e0) // full G
	      //	     || ((wbuf[i] & 0x001f) == 0x001f) // full B
	      ;
	  }
	  if(y >= threshold || is_special_color){
	    buf[i] = 1;
	  } else {
	    buf[i] = 0;
	  }
	} else {
	  buf[i] = buf[i*byte_per_pixel];
	  for(int j = 1; j < byte_per_pixel; j++){
	    buf[i] |= buf[i*byte_per_pixel+j];
	  }
	}
      }
    }
    if(scale > 1){
      for(int j = 0; j < height/scale; j++){
	for(int i = 0; i < width/scale; i++){
	  buf[j*width + i] = buf[j*width*scale + i*scale];
	}
      }
    }

    vfd.loadBitmapBytePerPixel(buf, width, height);
    
    //vfd.show();
    vfd.syncAndShow();
    if( fp != stdin ){
      rewind(fp);
    }
    
    time_elapsed = micros() - time_s;
    if( looptime > time_elapsed + 100){
      usleeptime = looptime - time_elapsed - 100;
      usleep(usleeptime);
    }
    time_elapsed = micros() - time_s;
    if( showinfo ){
      if( cnt % fps == 0 ){
	fprintf(stderr, "%d, %d usec(FPS=%.1lf)\r", cnt,
		(int)(time_elapsed), (double)1000000 / (time_elapsed));
      }
    }
  }
}
