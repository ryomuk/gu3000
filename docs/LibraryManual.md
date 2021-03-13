書きかけドラフト(2021/3/13版)


# グラフィックDMAモード用ライブラリ リファレンスマニュアル
GU3000Graphicクラス(VFDクラス)は，
描画機能を司るFrameBufferクラスと，ハードウェア(GPIO)を制御するGU3000GPIOクラスを継承して作られています．
VFDクラスはGU3000Graphicクラスと同一のもの(typedefで定義)です．
本マニュアルでは，それぞれのクラスとそれらの関数(メソッド)について説明します．
```
class GU3000Graphic : public FrameBuffer, private GU3000GPIO
typedef GU3000Graphic VFD;
```

# 概念図
描画はFrameBufferのbuf上に行われます．
buf[]はshow()メソッドによってVFDの表示メモリ(display_memory[])に転送されます．
VFDに送られた内容はm_buf[]にもコピーされます．

graphicDMAモードにおいてもVFDへの転送はそれなりに時間がかかるので，
差分が含まれるエリア(差分が開始したところから終了したところまで)を転送します．
```
+-------------------------------
|GU3000Graphic(= VFD)
| (typedef GU3000Graphic VFD)
|+-------------------+
|| FrameBuffer       |
||buf[WIDTH*HEIGHT]  |
|+-------------------+
|
|m_buf[WIDTH*HEIGHT*面数]
|
|+-------------------+
|| GU3000GPIO        |
||  RDY   WR D0-D7   |
|+-------------------+
+--------------------------------
    ↑    ↓  ↓
+--------------------------------
    RDY   WR D0-D7
|  VFDモジュール
|  display_memory[WIDTH*HEIGHT*面数]
+--------------------------------
```

# GU3000GPIO クラス
## Public関数
### void GU3000GPIO::init()
GPIOを下記デフォルト値で初期化します．(../src/gu3000gpio.h)
```c
#define VFD_RDY   18                // RDY信号
#define VFD_WR    19                // WR信号(負論理)
#define VFD_Data0 20                // データバスはData0から連番で8bit
```

### void GU3000GPIO::init(int rdy, int wr, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7)
GPIOを引数で初期化します．

### void GU3000GPIO::setBitmapOrder(int order)

## Protected関数
### void GU3000GPIO::writeByte(byte byteData)

### void GU3000GPIO::writeByteImage(byte byteData)
```
VFD hardware pixel mapping is MSB first (why??)
See software manual (section 5.2(page 63))
      x
y     0 1 2 3 4 5... 255
0  D7
   D6
   D5
   D4
   D3
   D2
   D1
   D0
1  D7
   D6
   D5
   D4
   .
   .
```

### void GU3000GPIO::writeWord(word wordData)

## private変数
###  int m_rdy; // GPIO pinnumber
###  int m_wr;  // GPIO pinnumber
###  int m_d0, m_d1, m_d2, m_d3, m_d4, m_d5, m_d6, m_d7;  // GPIO pinnumber
###  int m_bitmapOrder; // Bit Order of Image Data

## private関数
###  inline void waitRDY()

# FrameBufferクラス
## 座標系
左上が原点です．回転は実装していません．
```
(0, 0) ...          (WIDTH-1, 0)
.
.
.
(0, HEIGHT-1)       (WIDTH-1, HEIGHT-1)
```

## Public変数
### byte *buf
フレームバッファのメモリです．1bit/1ピクセル．
MycroPythonのframebufで言う，'MONO_VLSB'です．

VFDモジュールにあわせて，垂直方向にアドレスが並ぶようになっています．
VFDモジュールの表示メモリはMSBが上(座標が小さい側, MSB first)ですが，
普通はLSB firstだと思うので，LSB firstで実装しています．
MycroPythonのframebufにも'MONO_VMSB'は無かったので．
でもなぜかffmpegのrawvideoはMSB firstのようです．

### int WIDTH
### int HEIGHT
### int bufsize
WIDTH * HEIGHT / 8 です．ループで出てくることが多い値なので，個別の変数にしています．

### int cursor_x
文字描画用のカーソル位置(x座標)．

### int cursor_y
文字描画用のカーソル位置(y座標)．

### Font *font
文字描画用のフォント．

### Font **fontList
ライブラリ内蔵フォントのリスト．

## Public関数
### void FrameBuffer::init(int x, int y)

### void FrameBuffer::setCursor(int x, int y)

### int FrameBuffer::getPixel(int x, int y)

#### FrameBuffer::getPixelMSBfirst(int x, int y)

### void FrameBuffer::drawPixel(int x, int y, int pen)
###  void fill(byte b);
###  void clear();

## privage変数
###  int m_ybytes; // = HEIGHT / 8
###  byte *m_font_bitmap;
###  int m_font_width;
###  int m_font_height;
###  int m_font_xspace;
###  int m_font_yspace;
###  byte m_font_firstcode;
###  byte m_font_lastcode;
###  int m_font_num_chars;
###  int m_font_bytes;
###  int m_font_proportional = false;
###  const byte **m_pfont_bitmap_ptr = NULL;
###  int *m_pfont_width = NULL;

## private関数
###  void writeLine(int x0, int y0, int x1, int y1, int pen);
###  void writeFastVline(int x, int y, int vlength, int pen);
###  void writeFastHline(int x, int y, int hlength, int pen);
###  int bitmapContentWidth(const byte *bitmap, int width, int height);
###  const byte *bitmapContentTop(const byte *bitmap, int width, int height);

## GU3000Graphicクラス
GU3000Graphicクラスは，
FrameBufferクラスをpublicで，GU3000GPIOクラスをprivateで継承したクラスです．
グラフィックDMAモードのVFDにFrameBufferの内容を表示する機能を実装しています．

## Public変数
### int xsize
### int ysize

## Public関数
###  void init()
{
   init(VFD_Xdots, VFD_Ydots, VFD_DispMemSize);
};
### void init(int x, int y, int memsize);
###   void setDAD(word displayAddress); // displayAddress(for multiple VFD);
###   void setBitmapOrder(int order);

###   void setDisplayStartAddress(word displayStartAddress);
VFDモジュール内蔵コマンドに対応
###   void writeBitImage(word address,  word imagesize, byte *bitmap);
VFDモジュール内蔵コマンドに対応
###   void writeAreaBitImage(word address, word xbyte, word ybyte, byte *bitmap);
VFDモジュール内蔵コマンドに対応
###   void setBrightness(byte brightness);
VFDモジュール内蔵コマンドに対応
###   void syncNextCommand();
VFDモジュール内蔵コマンドに対応

###  void updateDisplayStartAddress();    // address = DisplayStartAddress
###  void rotateAndSetDisplayStartAddress(); 
###  void rotateButNotSetDisplayStartAddress();
###  void clear();
###    void clearFrameBuffer();
###    void show();
###    void rotateAndShow();
###    void syncAndShow();
###    void syncRotateAndShow();
###    void showAllArea();
## private変数
###  byte *m_buf = NULL;
###  bool m_first_show;
###  word m_disp_memsize;
###  word m_disp_areasize;
###  word m_disp_startaddr;
###  word m_dad = VFD_DAD_BROADCAST;
## private関数
###  void flushCommandData();
###  void writeCommand(byte command);
###  // DAD(Display Address for using multiple VFD modules)

