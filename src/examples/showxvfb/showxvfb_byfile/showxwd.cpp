#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// X11 include files need to install xorg-dev (% apt install xorg-dev)

#define Font Font_X11  // to avoid typedef confliction
#include <X11/Xlib.h>
#undef Font
//#include <X11/Xutil.h>
#include <X11/XWDFile.h>

#include <gu3000graphic.h>

void Error(const char *msg){
  fprintf(stderr, msg);
  exit(1);
}

static void
_swapshort(char *bp, unsigned int n)
{
    register char c;
    register char *ep = bp + n;

    while (bp < ep) {
	c = *bp;
	*bp = *(bp + 1);
	bp++;
	*bp++ = c;
    }
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

#if 0 // fordebug
static void
DumpHeader(const XWDFileHeader *header, const char *win_name)
{
	printf("window name:        \"%s\"\n", win_name);
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

static Bool
Read(char *ptr, int size, int nitems, FILE *stream)
{
    size *= nitems;
    while (size) {
	nitems = fread(ptr, 1, size, stream);
	if (nitems <= 0)
	    return False;
	size -= nitems;
	ptr += nitems;
    }
    return True;
}

int main(int argc, char *argv[]){
  int i;
  VFD vfd;
  FILE *fp = stdin;
  long buftop;
  
  XWDFileHeader header;
  int win_name_size;
  char *win_name;
  //Bool rawbits = False;
int ncolors;
  XColor *colors;
  XWDColor xwdcolor;
  
  byte *buf;
  int bufsize;
  
  if(argc > 1){
    if((fp = fopen(argv[1], "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], argv[1]);
      exit(1);
    }
  }

  fread((char *)&header, sizeof(XWDFileHeader), 1, fp);
  _swaplong((char *)&header, sizeof(XWDFileHeader));
  
  /* alloc window name */
  win_name_size = (header.header_size - SIZEOF(XWDheader));
  if (win_name_size < 1)
    Error("win_name_size");
  if((win_name = (char *)malloc((unsigned) win_name_size + 6)) == NULL)
    Error("Can't malloc window name storage.");
  strcpy(win_name, "xwud: ");
  
  /* read in window name */
  if(!fread(win_name + 6, sizeof(char), win_name_size, fp))
    Error("Unable to read window name from dump file.");
  (win_name + 6)[win_name_size - 1] = 0;
  

  //  DumpHeader(&header, "");
  
  /* read in the color map buffer */
  if((ncolors = header.ncolors)) {
    colors = (XColor *)malloc((unsigned) ncolors * sizeof(XColor));
    if (!colors)
      Error("Can't malloc color table");
    for (i = 0; i < ncolors; i++) {
      if(!Read((char *) &xwdcolor, SIZEOF(XWDColor), 1, fp))
	Error("Unable to read color map from dump file.");
      colors[i].pixel = xwdcolor.pixel;
      colors[i].red = xwdcolor.red;
      colors[i].green = xwdcolor.green;
      colors[i].blue = xwdcolor.blue;
      colors[i].flags = xwdcolor.flags;
    }
    for (i = 0; i < ncolors; i++) {
      _swaplong((char *) &colors[i].pixel, sizeof(long));
      _swapshort((char *) &colors[i].red, 3 * sizeof(short));
    }
  } else {
    /* no color map exists, turn on the raw option */
    // rawbits = True;
  }
  
  bufsize = vfd.WIDTH * vfd.HEIGHT;
  if((buf = (byte *)malloc(bufsize)) == NULL){
    fprintf(stderr, "%s: malloc() failed.\n", argv[0]);
    exit(1);
  }
  
  buftop = ftell(fp);
  fread(buf, sizeof(byte), bufsize, fp);
  vfd.loadBitmapBytePerPixel(buf, vfd.WIDTH, vfd.HEIGHT);
  vfd.show();
  fclose(fp);

  while(1){
    int time_s, time_e;
    
    time_s = micros();
    
    if((fp = fopen(argv[1], "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], argv[1]);
      exit(1);
    }
    
    
    fseek(fp, buftop, SEEK_SET);
    fread(buf, sizeof(byte), bufsize, fp);

    vfd.loadBitmapBytePerPixel(buf, vfd.WIDTH, vfd.HEIGHT);
    vfd.show();
    fclose(fp);

    time_e = micros();
    printf("%d usec(%dFPS)\n",
	   (int)(time_e - time_s),
	   (int)(1000000.0/(time_e - time_s))
	   );
  }
}
