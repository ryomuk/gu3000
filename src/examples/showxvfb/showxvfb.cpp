#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h> // for usleep()

// X11 include files need to install xorg-dev (% apt install xorg-dev)

#define Font Font_X11  // to avoid typedef confliction
#include <X11/Xlib.h>
#undef Font
//#include <X11/Xutil.h>
#include <X11/XWDFile.h>

#include <gu3000graphic.h>

void Error(const char *msg){
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

static void
_swaplong(char *bp, unsigned int n)
{
    register char c;
    register char *ep = bp + n;
    register char *sp;

    while (bp < ep) {
	sp = bp + 3;
	c = *sp;
	*sp = *bp;
	*bp++ = c;
	sp = bp + 1;
	c = *sp;
	*sp = *bp;
	*bp++ = c;
	bp += 2;
    }
}

#if 0 // for debug
static void
DumpHeader(const XWDFileHeader *header, const char *win_name)
{
  //	printf("window name:        \"%s\"\n", win_name);
	printf("sizeof(XWDheader):  %d\n", (int)sizeof(*header));
	printf("header size:        %d\n", (int)header->header_size);
	printf("file version:       %d\n", (int)header->file_version);
	printf("pixmap format:      %d\n", (int)header->pixmap_format);
	printf("pixmap depth:       %d\n", (int)header->pixmap_depth);
	printf("pixmap width:       %d\n", (int)header->pixmap_width);
	printf("pixmap height:      %d\n", (int)header->pixmap_height);
	printf("x offset:           %d\n", (int)header->xoffset);
	printf("byte order:         %d\n", (int)header->byte_order);
	printf("bitmap unit:        %d\n", (int)header->bitmap_unit);
	printf("bitmap bit order:   %d\n", (int)header->bitmap_bit_order);
	printf("bitmap pad:         %d\n", (int)header->bitmap_pad);
	printf("bits per pixel:     %d\n", (int)header->bits_per_pixel);
	printf("bytes per line:     %d\n", (int)header->bytes_per_line);
	printf("visual class:       %d\n", (int)header->visual_class);
	printf("red mask:           %d\n", (int)header->red_mask);
	printf("green mask:         %d\n", (int)header->green_mask);
	printf("blue mask:          %d\n", (int)header->blue_mask);
	printf("bits per rgb:       %d\n", (int)header->bits_per_rgb);
	printf("colormap entries:   %d\n", (int)header->colormap_entries);
	printf("num colors:         %d\n", (int)header->ncolors);
	printf("window width:       %d\n", (int)header->window_width);
	printf("window height:      %d\n", (int)header->window_height);
	printf("window x:           %d\n", (int)header->window_x);
	printf("window y:           %d\n", (int)header->window_y);
	printf("border width:       %d\n", (int)header->window_bdrwidth);
}
#endif

int main(int argc, char *argv[]){

  int shmid = 0;
  VFD vfd;
  XWDFileHeader header;
  XWDFileHeader *header_p;

  byte *buf;

  if(argc > 1){
    shmid = atoi(argv[1]);
  }

  printf("shmid=%d\n", shmid);

  if((header_p = (XWDFileHeader *)shmat(shmid, 0, 0)) == (void *) -1){
    Error("shmat() failed");
  }

  header = *header_p;
  _swaplong((char *)&header, sizeof(XWDFileHeader));

  // DumpHeader(&header, "");

  buf = (byte *)header_p
    + header.header_size + sizeof(XColor) * header.ncolors;
  
  //struct timespec ts;
  //ts.tv_sec = 0;
  //ts.tv_nsec = 10*1000*1000;
  while(1){
    int time_s, time_e;
    time_s= micros();

    vfd.loadBitmapBytePerPixel(buf, vfd.WIDTH, vfd.HEIGHT);
    vfd.show();
    //nanosleep(&ts, NULL);
    //delayMicroseconds(25*1000);
    usleep(25*1000);
    time_e = micros();
    printf("%d usec(%dFPS)\r",
	   (int)(time_e - time_s),
	   (int)(1000000.0/(time_e - time_s))
	   );
    // raspberry pi zero : 60FPS (no wait)
  }
}
