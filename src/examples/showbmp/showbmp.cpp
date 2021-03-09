#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep

#include <gu3000graphic.h>

#define BMP_FORMAT_BMP     0
//#define BMP_FORMAT_XWD     1
#define BMP_FORMAT_RAWBIT  2
#define BMP_FORMAT_RAWBYTE 3

typedef struct {
    int width;
    int height;
} BitmapSize;

void Error(const char *msg){
  fprintf(stderr, msg);
  exit(1);
}

#pragma pack(1)
typedef struct{
  unsigned short bfType;
  unsigned int   bfSize;
  unsigned short bfReserverd1;
  unsigned short bfReserverd2;
  unsigned int   bfOffBits;
} BitmapFileHeader;
#pragma pack()

#pragma pack(1)
typedef struct{
  unsigned int biSize;
  int biWidth;
  int biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  int biXpixPerMeter;
  int biYPixPerMeter;
  unsigned int biClrUser;
  unsigned int biCirImportant;
} BitmapInformationHeader;
#pragma pack()

byte *read_bmp_file(FILE *fp, BitmapSize *size){
  byte *buf;
  int bufsize;

  BitmapFileHeader fHeader;
  BitmapInformationHeader iHeader;
  
  fread(&fHeader, sizeof(BitmapFileHeader), 1, fp);
  fread(&iHeader, sizeof(BitmapInformationHeader), 1, fp);

  int skipSize = fHeader.bfOffBits - sizeof(BitmapFileHeader)
    - sizeof(BitmapInformationHeader);
  if(skipSize > 0){
    fseek(fp, skipSize, SEEK_CUR);
  }

  printf("%c%c(%04x) ", (char)fHeader.bfType, (char)(fHeader.bfType>>8), fHeader.bfType);
  printf("bfOffBits=%d ", fHeader.bfOffBits);
  printf("biWidth=%08x ", iHeader.biWidth);
  printf("biHeight=%08x ", iHeader.biHeight);
  printf("biSizeImage=%08x ", iHeader.biSizeImage);
  printf("skipSize=%d ", skipSize);
  printf("sizeof(BitmapFileHeader)=%d ", sizeof(BitmapFileHeader));
  printf("sizeof(BitmapInformationHeader)=%d ", sizeof(BitmapInformationHeader));
  printf("\n");	 

  if( fHeader.bfType != 0x4d42){
    fprintf(stderr, "Not a BMP file (Header format error).\n");
    exit(1);
  }
  
  bufsize = iHeader.biSizeImage;
  
  if((buf = (byte *)malloc(bufsize)) == NULL){
    fprintf(stderr, "malloc() failed.\n");
    exit(1);
  }

  fread(buf, sizeof(byte), bufsize, fp);

  size->width = iHeader.biWidth;
  size->height = iHeader.biHeight;

  return(buf);
}

byte *read_rawfile(FILE *fp, int bufsize){
  byte *buf;

  if((buf = (byte *)malloc(bufsize)) == NULL){
    fprintf(stderr, "malloc() failed.\n");
    exit(1);
  }
  fread(buf, sizeof(byte), bufsize, fp);
  return buf;
}

void usage(){
  fprintf(stderr, "Usage: showbmp [OPTION]... [FILE]\n");
  fprintf(stderr, "  -w[idth] width: set width (default=256)\n");
  fprintf(stderr, "  -h[eight] height: set height (default=128)\n");
  fprintf(stderr, "  -bpp: bit per pixel (8, 16, 24, 32...) used with -rawbyte");
  fprintf(stderr, "  -rawbit: raw bit/pixel file\n");
  fprintf(stderr, "  -rawbyte: raw byte/pixel file\n");
  fprintf(stderr, "  -offset: setoffset(byte)\n");
  fprintf(stderr, "  -bmp: .bmp file (default)\n");
  fprintf(stderr, "  -loop: loop forever\n");
  fprintf(stderr, "  -fb: = showbmp -loop -rawbyte -bpp 16 /dev/fb0\n");
  exit(1);
}

int main(int argc, char *argv[]){
  unsigned long time_s, time_e;
  
  VFD vfd;
  FILE *fp = stdin;
  char *filename = NULL;

  byte *buf = NULL;
  int bufsize;
  int bmp_format = BMP_FORMAT_BMP;
  BitmapSize size = { .width = vfd.xsize,
		      .height = vfd.ysize};
  int bit_per_pixel;
  int byte_per_pixel;
  int offset = 0;
  
  bool loop = false;
  bool firstloop = true;
  
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      /*  */ if(strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-width") == 0){
	i++;
	if(i >= argc) usage();
	size.width = atoi(argv[i]);
      } else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-height") == 0){
	i++;
	if(i >= argc) usage();
	size.height = atoi(argv[i]);
      } else if(strcmp(argv[i], "-rawbit") == 0){
	bmp_format = BMP_FORMAT_RAWBIT;
	bit_per_pixel = 1;
      } else if(strcmp(argv[i], "-rawbyte") == 0){
	bmp_format = BMP_FORMAT_RAWBYTE;
	bit_per_pixel = 8;
      } else if(strcmp(argv[i], "-bmp") == 0){
	bmp_format = BMP_FORMAT_BMP;
	bit_per_pixel = 1;
      } else if(strcmp(argv[i], "-bpp") == 0){
	i++;
	if(i >= argc) usage();
	bit_per_pixel = atoi(argv[i]);
      } else if(strcmp(argv[i], "-offset") == 0){
	i++;
	if(i >= argc) usage();
	offset = atoi(argv[i]);
      } else if(strcmp(argv[i], "-loop") == 0){
	loop = true;
      } else if(strcmp(argv[i], "-fb") == 0){
	loop = true;
	bit_per_pixel = 16;
	bmp_format = BMP_FORMAT_RAWBYTE;
	filename = (char *) "/dev/fb0";
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
  if( filename == NULL){
    fp = stdin;
  } else {
    if((fp = fopen(filename, "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], filename);
      exit(1);
    }
  }

  byte_per_pixel = bit_per_pixel / 8;
  do{
    switch(bmp_format){
    case BMP_FORMAT_BMP: 
      buf = read_bmp_file(fp, &size); break;
    case BMP_FORMAT_RAWBIT:
      bufsize = size.width * size.height / 8 + offset;
      buf = read_rawfile(fp, bufsize);
      buf += offset;
      break;
    case BMP_FORMAT_RAWBYTE:
      bufsize = size.width * size.height * byte_per_pixel + offset;
      buf = read_rawfile(fp, bufsize);
      buf += offset;
      break;
    default:
      /* never occur */
      exit(0);
    }
    
    if( bmp_format == BMP_FORMAT_RAWBYTE && byte_per_pixel > 1){
      for(int i = 0; i < size.width * size.height; i++){
	buf[i] = buf[i*byte_per_pixel];
	for(int j = 1; j < byte_per_pixel; j++){
	  buf[i] |= buf[i*byte_per_pixel+j];
	}
      }
    }
    
    if(firstloop){
      if(bmp_format == BMP_FORMAT_RAWBIT ||
	 bmp_format == BMP_FORMAT_RAWBYTE ){
	printf("width=%d, height=%d, bpp=%d, offset=%d, filename='%s'\n",
	       size.width, size.height, bit_per_pixel, offset, filename);
      }
      firstloop = false;
    }
    
    time_s = micros();
    //  vfd.loadBitmapHMSB(buf, iHeader.biWidth, iHeader.biHeight);
    switch(bmp_format){
    case BMP_FORMAT_BMP:
      vfd.loadBitmapBMP(buf, size.width, size.height);
      break;
    case BMP_FORMAT_RAWBIT:
      vfd.loadBitmapHLSB(buf, size.width, size.height);
      break;
    case BMP_FORMAT_RAWBYTE:
      vfd.loadBitmapBytePerPixel(buf, size.width, size.height);
      break;
    }
    time_e = micros();
    
    vfd.show();
    printf("%d usec\r", (int)(time_e - time_s));
    if(loop){
      rewind(fp);
      free(buf);
      usleep(25*1000);
    }
  } while (loop);
  printf("\n");
}
