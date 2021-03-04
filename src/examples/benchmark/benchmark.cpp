#include <stdio.h>
#include <stdlib.h>
#include <gu3000graphic.h>

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

int main(int argc, char *argv[]){
  unsigned long time_s, time_lastcommand;

  VFD vfd;
  FILE *fp = stdin;
  byte *buf;

  if(argc > 1){
    if((fp = fopen(argv[1], "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], argv[1]);
      exit(1);
    }
  }
  
  BitmapFileHeader fHeader;
  BitmapInformationHeader iHeader;
  
  fread(&fHeader, sizeof(BitmapFileHeader), 1, fp);
  fread(&iHeader, sizeof(BitmapInformationHeader), 1, fp);

  int skipSize = fHeader.bfOffBits - sizeof(BitmapFileHeader) - sizeof(BitmapInformationHeader);
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

  int bufsize = iHeader.biSizeImage;
  
  if((buf = (byte *)malloc(bufsize)) == NULL){
    fprintf(stderr, "%s: malloc() failed.\n", argv[0]);
    exit(1);
  }

  fread(buf, sizeof(byte), bufsize, fp);
  
  time_s = micros();
  //  vfd.loadBitmapHMSB(buf, iHeader.biWidth, iHeader.biHeight);
  vfd.loadBitmapBMP(buf, iHeader.biWidth, iHeader.biHeight);
  time_lastcommand = micros() - time_s;
  printf("loadBitmapBMP: %d usec\n", (int)time_lastcommand);
	 
  vfd.show();
  
  time_s = micros();
  vfd.clear();
  time_lastcommand = micros() - time_s;
  printf("clear:%d usec\n", (int)time_lastcommand);

#if 0
  for(int i = 1; i <= vfd.bufsize; i++){
    time_s = micros();
    vfd.writeBitImage(0, i, vfd.buf);
    time_lastcommand = micros() - time_s;
    printf("writeBitImage %d byte: %d usec\n", i, (int)time_lastcommand);
  }
#endif
#if 1  
  for(int x = 1; x <= vfd.xsize; x++){
    for(int y = 1; y <= vfd.ysize/8; y++){
      time_s = micros();
      vfd.writeAreaBitImage(0, x+1, y+1, vfd.buf);
      time_lastcommand = micros() - time_s;
      printf("writeAreaBitImage %d x %d = %d byte: %d usec\n",
	     x, y, x*y,
	     (int)time_lastcommand);
    }
  }
#endif

}
