#include <stdio.h>
#include <stdlib.h>
#include <gu3000graphic.h>

#define DEFAULT_FONTNAME "Noritake6x8"

void usage(){
  fprintf(stderr, "Usage: viewtxt [OPTION]\n");
  fprintf(stderr, "  -f fontname : select font\n");
  fprintf(stderr, "  -l : show fontname list\n");
  exit(1);
}

void showfontlist(FrameBuffer *fb){
  for(int i = 0; fb->fontList[i] != NULL; i++){
    printf("%s\n", fb->fontList[i]->name);
  }
}

bool getpixel(Font *f, int c, int x, int y){
  const byte *bitmap;
  int memoffset, height_bytes;
  byte bitpattern;

  height_bytes = f->height / 8;
  if(f->height & 7){
    height_bytes++;
  }

  bitmap = &(f->bitmap[height_bytes * f->width * (c - f->firstcode)]);

  memoffset = x*height_bytes + (y / 8);
  bitpattern = bit(y & 7);
  return((bitmap[memoffset] & bitpattern) != 0);
}

int main(int argc, char *argv[]){
  FrameBuffer fb(0, 0);
  Font *f;

  const char *fontname = NULL;
  
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      switch(argv[i][1]){
      case 'f':
	i++;
	if(i >= argc) usage();
	fontname = argv[i];
	break;
      case 'h':
	usage();
	break;
      case 'l':
	showfontlist(&fb);
	exit(0);
      default:
	usage();
      }
    } else {
      usage();
    }
  }

  // Fixed width
  if(fontname == NULL){
    fontname = DEFAULT_FONTNAME;
  }

  f = fb.getFontByName(fontname);

  printf("++font-text-file\n");
  printf("++chars\n");
  printf("256\n");
  printf("++width\n");
  printf("%d\n", f->width + f->xspace);
  printf("++height\n");
  printf("%d\n", f->height + f->yspace);
  
  for(int c = 0; c <= 0xff; c++){
    if(c < 0x20){
      printf("++---%03d-0x%02x-----\n", c, c);
    } else {
      printf("++---%03d-0x%02x-'%c'-\n", c, c, c);
    }
    if(c >= f->firstcode && c <= f->lastcode){
      for(int j = 0; j < f->height; j++){
	for(int i = 0; i < f->width; i++){
	  if(getpixel(f, c, i, j)){
	    putchar('X');
	  } else {
	    putchar(' ');
	  }
	}
	putchar('\n');
      }
    }
  }
}

