#include <stdio.h>
#include <stdlib.h>
#include <gu3000normal.h>
#include <framebuffer.h>

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

byte swapbit8(byte x){
  int y = 0;
  for(int i = 0; i < 8; i++){
    y <<= 1;
    y = y | (x & 1);
    x >>= 1;
  }
  return y;
}

int main(int argc, char *argv[]){
  VFD vfd;
  FILE *fp;

  if(argc <= 1){
    fp = stdin;
  } else {
    fp = fopen(argv[1], "r");
    if( fp == NULL){
      perror("fopen");
      exit(EXIT_FAILURE);
    }
  }
  
  FrameBuffer fbOut(vfd.xsize, vfd.ysize);
  
  BitmapFileHeader fHeader;
  BitmapInformationHeader iHeader;
    
  //vfd.setBrightness(VFD_BRIGHTNESS_OFF);
  vfd.setBrightness(VFD_BRIGHTNESS_MID);
  
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

  FrameBuffer fbIn(iHeader.biHeight, iHeader.biWidth);

  // Clear frame buffer
  fbIn.clear();
  fbOut.clear();

  fread(fbIn.buf, sizeof(byte), iHeader.biSizeImage, fp);

  for(unsigned int i = 0; i < iHeader.biSizeImage; i++){
    fbIn.buf[i] = swapbit8(fbIn.buf[i]);
  }
  
  for(int i = 0 ; i < vfd.xsize; i++){
    for(int j = 0; j < vfd.ysize; j++){
      if(fbIn.getPixel(vfd.ysize-j, i)){
	fbOut.pset(i, j);
      }
    }
  }

  vfd.writeBitImage(0, fbOut.bufsize, fbOut.buf);
  //  vfd.setDisplayStartAddress(vfd.screenAddress(0));
}
