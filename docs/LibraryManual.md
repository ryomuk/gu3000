書きかけドラフト(2021/3/16版)


# GU3000Graphicクラス(グラフィックDMAモード用ライブラリ)リファレンスマニュアル
GU3000Graphicクラス(VFDクラス)は，
描画機能を提供するFrameBufferクラスと，ハードウェア(GPIO)を制御するGU3000GPIOクラスを継承して作られています．
VFDクラスはGU3000Graphicクラスと同一のもの(typedefで定義)です．
本マニュアルでは，それぞれのクラスとそれらの関数(メソッド)について説明します．
```
class GU3000Graphic : public FrameBuffer, private GU3000GPIO
typedef GU3000Graphic VFD;
```

グラフィックDMAモードの詳細についてはVFDモジュールの仕様書「基本機能ソフトウェア仕様書 5章 グラフィックDMAモード」を参照して下さい．

# ライブラリビルド方法
```
git clone https://github.com/ryomuk/gu3000.git
cd gu3000/src
make
```
これで，静的ライブラリ gu3000.a が出来ます．

# ユーザプログラムの例
gu3000graphic.hをインクルードして下さい．

プログラム例 hello.cpp
```c
#include <gu3000graphic.h>

int main(){
  VFD vfd;
  vfd.puts("Hello World!");
  vfd.show();
}
```

# リンク方法
wiringPi，およびgu3000.aをリンクして下さい．
直接コンパイルのコマンドを入力する場合は，下記の例のようにします．
```
cd gu3000/src/examples/hello
g++ -c hello.cpp -I../..
g++ -o hello hello.o ../../gu3000.a -lwiringPi -I../..
```
ライブラリやinclude用のパスは，Makefile等で適宜設定して下さい．

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
## ソースファイル
- gu3000gpio.h
- gu3000gpio.cpp
## Public関数
### void GU3000GPIO::init()
GPIOのピンを下記デフォルト値で設定します．
データバスはData0から8bitの連番に設定されます．
```c
#define VFD_RDY   18                // RDY信号ピン番号
#define VFD_WR    19                // WR信号(負論理)ピン番号
#define VFD_Data0 20                // Data0ピン番号
```

### void GU3000GPIO::init(int rdy, int wr, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7)
GPIOのピンを引数に従って設定します．

### void GU3000GPIO::setBitmapOrder(int order)
VFDモジュールのピクセルの並びは下記のようになっています．
(「ディスプレイモジュール3900Bシリーズ"基本機能"ソフトウェア仕様書」
5章 グラフィックDMAモード, 5.2節 表示メモリ 参照)

アドレスは上から下に増加しますが，1バイト(8ピクセル)中は，MSBが上，LSBが下です．

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

好みの問題かもしれませんが，これは若干気持が悪いので，FrameBufferクラスではLSBが上，MSBが下として描画処理を実装しています．
ビットマップ画像もこの格納方法に従います．

GU3000GPIO::writeByteImage()でVFDへに画像(bitmapimage)の書き込む際に，
プライベート変数m_bitmaporderの値によって，
D0〜D7の順かD7〜D0の順かを切り替えています．
デフォルトの設定はLSB firstです．
```c
//
// Bit Order of Image Data for writeByteImage()
//
#define VFD_MSBFIRST 0
#define VFD_LSBFIRST 1
#define VFD_DEFAULT_BITMAPORDER VFD_LSBFIRST
```

### void GU3000GPIO::writeByte(byte byteData)
GPIO経由で1バイト書き込む．

### void GU3000GPIO::writeByteImage(byte byteData)
GPIO経由で1バイトのbitmapイメージ(縦8bitx横1bit)を書き込む．
データがMSB first(上がMSB)かLSB first(上がLSB)かは，
m_bitmaporder(デフォルト値はLSB first)で設定しておく．

VFD側は上がMSBなので，デフォルトの設定では
イメージデータはテレコになって書き込まれる．

### void GU3000GPIO::writeWord(word wordData)
GPIO経由で1ワード(2バイト)書き込む．

## private変数
###  int m_rdy
RDY信号(入力)のGPIOピン番号です．

###  int m_wr
WR信号(出力, 負論理)のGPIOピン番号です．

###  int m_d0, m_d1, m_d2, m_d3, m_d4, m_d5, m_d6, m_d7
Data0〜Data7(出力)のGPIOピン番号です．

###  int m_bitmapOrder
ビットマップがLSB firstかMSB firstかを指定するための変数です．

## private関数
###  inline void waitRDY()
VFDモジュールからのRDY信号がアクティブになるのを待ちます．
通常の待ち時間はマイクロ秒レベルなので，
割り込み等ではなくひたすらポーリングするループです．
モジュールがつながっていないとここで止まってしまうので，
その場合はVFD_DEGUB_IGNORE_RDYを#defineしてコンパイルします．
(RDYをプルアップしておけばいいのかも．)
```c
inline void waitRDY(){
#ifndef VFD_DEGUB_IGNORE_RDY
    while(!digitalRead(m_rdy)){
    }
#endif
```

# FrameBufferクラス
簡易的な描画機能を提供するクラスです．

## ソースファイル
- framebuffer.h
- framebuffer.cpp
- font.h
- font.cpp
- fonts/*.h

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
フレームバッファの幅．

### int HEIGHT
フレームバッファの高さ．

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
### void FrameBuffer::init(int width, int height)
WIDTH = x, HEIGHT = yで初期化．bufを確保します．
フォントをデフォルト(g_DefaultFont)に設定します．

## Public関数(描画関連)
###  void fill(byte c)
buf[0..bufsize]をcで埋めます．

###  void FrameBuffer::clear() (== GU3000Graphic::clearFrameBuffer())
bufをゼロクリアして，カーソル位置を(0,0)にします．
GU3000Graphicクラスでは，clearFrameBuffer() で呼びます．
(参考: 
GU3000Graphic::clear()はフレームバッファのクリアに加えて，
VFDモジュールの表示メモリもクリアします．)

###  inline void pset(int x, int y)
(x, y)にピクセルを描画します．
高速にするために，定義域のエラーチェックをしていないことに注意．

###  inline void preset(int x, int y)
(x, y)のピクセルを消します．
高速にするために，定義域のエラーチェックをしていないことに注意．

###  int getPixel(int x, int y)
(x, y)のピクセル値を返します．
ピクセルが無ければ0, ピクセルがあれば，(1<<(y&7))を返します．
(x, y)がフレームバッファの範囲外の場合は0を返します．

###  int getPixelMSBfirst(int x, int y)
各バイトがMSB first(MSBが上)の場合の(x, y)のピクセル値を返します．
ピクセルが無ければ0, ピクセルがあれば，(1<<(7-(y&7)))を返します．
(x, y)がフレームバッファの範囲外の場合は0を返します．

###  void drawPixel(int x, int y, int pen)
(x, y)のピクセルを描画/消去します．(pen!=0: 描画, pen==0: 消去)
(x, y)がフレームバッファの範囲外の場合は何もしません．

###  void drawLine(int x0, int y0, int x1, int y1, int pen)
(x0, y0)から(x1, y1)までの線を描画/消去します．(pen!=0: 描画, pen==0: 消去)
水平線はwriteFastHline，垂直線はwriteFastVline,
それ以外はwriteLineにディスパッチしています．

###  void drawBox(int x0, int y0, int x1, int y1, int pen)
四角形(辺だけ)を描画，消去します．(pen!=0: 描画, pen==0: 消去)

###  void drawBoxFill(int x0, int y0, int x1, int y1, int pen)
四角形(内部塗りつぶし)を描画，消去します．(pen!=0: 描画, pen==0: 消去)

###  void drawBitmap(int x, int y, const byte *bitmap, int width, int height)
座標(x, y)から(x+width-1, y+height-1)を対角線とする矩形エリアに，
幅width, 高さheightのビットマップ画像を描画します．

## Public関数(文字描画関連)
###  void putchar(int c)
現カーソル位置に文字を描画してカーソルを進めます．
描画スペースが無い場合はスクロールします．

###  void puts(const char *s)
現カーソル位置に文字列を描画してカーソルを進めます．
描画スペースが無い場合はスクロールします．

###  void drawChar(int x, int y, byte c)
座標(x, y)に文字を描画します．カーソル位置は変えません．

###  void setCursor(int x, int y)
文字描画用のカーソル位置(文字の左上)を(x, y)に設定します．

###  void scrollByte()
1バイト(8ピクセル)分，上にスクロールします．

###  void setTabstop(int n)
タブストップの位置をnの倍数文字目に設定します．

## Public関数(フォント関連)
###  void setFont(Font *font)
文字描画用のフォントをフォントデータへのポインタで設定する．
フォントデータの実体はfonts/*.hに記載されており，
font.cppがインクルードし，Font *型のグローバル変数(定数)になっています．

###  void setFontByName(const char *fontname)
文字描画用のフォントをフォント名で設定する．

###  Font *getFontByName(const char *fontname)
フォント名を引数とし，フォントデータへのポインタを返します．

###  void setFontDefault()
デフォルトのフォントを描画用に設定します．下記と等価です．
```cい
setFontByName(FONT_DEFAULT_FONTNAME)
```
デフォルト値は下記の通りです．(font.hに記載)
```c
#define FONT_DEFAULT_FONTNAME "Noritake6x8"
```

###  void setFontProportional()
現在設定されているフォントを元に，
プロポーショナルフォントで描画するため
のフォントビットマップテーブル(*m_pfont_bitmap_ptr[])と，
文字幅のテーブル(m_pfont_width[])を作成します．

###  void setFontFixedWidth()
文字描画を固定幅フォントで描画するように設定します．

###  void invertFontBitmapOrder()
setBitmapOrder(VFD_MSBFIRST)に設定した場合の文字描画用にフォントデータを変換します．

## Public関数(全画面ビットマップ描画関連)
###  void loadBitmapHLSB(byte *bmp, int width, int height)
水平方向でLSB firstのビットマップ画像をbufに読み込みます．

###  void loadBitmapBMP(byte *bmp, int width, int height)
BMPファイル形式のコンテンツのビットマップ画像をbufに読み込みます．

###  void loadBitmapBytePerPixel(byte *bmp, int width, int height)
1byte/pixelのビットマップ画像をbufに読み込みます．

## private変数
###  int m_ybytes
m_ybytes = HEIGHT / 8 です．出現頻度が多いので，専用の変数にしています．

###  byte *m_font_bitmap
現在のフォントのビットマップデータへのポインタです．

###  int m_font_width
現在のフォントの幅です．

###  int m_font_height
現在のフォントの高さです．

###  int m_font_xspace
フォント描画時のx方向の余白です．

###  int m_font_yspace
フォント描画時のy方向の余白です．

###  byte m_font_firstcode
現在のフォントの先頭コードの値です．

###  byte m_font_lastcode
現在のフォントの末尾コードの値です．

###  int m_font_bytes
フォントのbitmapの1文字あたりのバイト数です．

###  int m_font_proportional
文字の描画をプロポーショナルにするか固定幅にするかのフラグです．
(false: 固定幅, true: プロポーショナル)

###  const byte **m_pfont_bitmap_ptr
setFontPropotional()が生成する，
プロポーショナルフォント用のビットマップデータのテーブルです．

###  int *m_pfont_width
setFontPropotional()が生成する，
プロポーショナルフォントの各文字の幅のテーブルです．

## private関数
###  void writeLine(int x0, int y0, int x1, int y1, int pen);
(x0, y0)から(x1, y1)までの線を描画します．
drawLineから呼ばれます．

###  void writeFastVline(int x, int y, int vlength, int pen);
(x, y)から長さvlengthの垂直線を描画します．

###  void writeFastHline(int x, int y, int hlength, int pen);
(x, y)から長さhlengthの水平線を描画します．

###  int bitmapContentWidth(const byte *bitmap, int width, int height);
ビットマップ画像の空白ではない部分の幅を返します．
setFontProportional()で，プロポーショナルフォントの文字幅テーブルを作成するための関数です．

###  const byte *bitmapContentTop(const byte *bitmap, int width, int height);
ビットマップ画像の空白ではない部分のy座標(最左が0)を返します．
setFontProportional()で，プロポーショナルフォントのビットマップデータテーブルを作成するための関数です．

## フォント型
```c
typedef struct {
  const byte *bitmap; // VLSB(垂直方向, LSB first)のビットマップデータ
  const char *name;   // getFontByName(), setFontByName() で使われる名前
  int width;          // 文字の幅
  int height;         // 文字の高さ
  int xspace;         // x方向の余白
  int yspace;         // y方向の余白
  int firstcode;      // 最初の文字コード
  int lastcode;       // 最後の文字コード
} Font;
```

## フォント関連グローバル変数
### extern Font *g_FontList[];
フォントデータのリストです．font.cppで，
fonts/*.h に記述されたフォントデータの実体を列挙して定義されます．

## GU3000Graphicクラス
GU3000Graphicクラスは，
FrameBufferクラスをpublicで，GU3000GPIOクラスをprivateで継承したクラスです．
グラフィックDMAモードのVFDにFrameBufferの内容を表示する機能を実装しています．

## ソースファイル
- gu3000graphic.h
- gu3000graphic.cpp

## Public変数
### int xsize
VFDモジュールのx方向(横)のドット数です．
### int ysize
VFDモジュールのy方向(縦)のドット数です．

## Public関数

###  void init()
デフォルト値で初期化します．
```
   init(VFD_Xdots, VFD_Ydots, VFD_DispMemSize, VFD_DAD_BROADCAST);
```
### void init(int x, int y, int memsize, DAD);
引数に従って初期化します．
- x: x方向(横)ドット数
- y: y方向(縦)ドット数
- memsize: VFDモジュールの総バッファサイズ(表示エリア+非表示エリア)
- DAD: VFDモジュールのアドレス(マニュアルでDADと呼ばれているもの)

###   void setDAD(word displayAddress); // displayAddress(for multiple VFD);
VFDモジュールのアドレス(マニュアルでDADと呼ばれているもの)を設定します．
ブロードキャストの場合は0xffです．

###   void setBitmapOrder(int order);
GU3000GPIO::setBitmapOrder() と同じものです．

###   void writeBitImage(word address,  word imagesize, byte *bitmap)
指定されたVFD表示メモリのアドレスにビットイメージデータを書き込みます．
VFDモジュールのコマンド(ビットイメージ書き込み, 5.4.1.1節)に対応します．

###   void writeAreaBitImage(word address, word xbyte, word ybyte, byte *bitmap)
指定されたエリアにビットイメージを書き込みます．
VFDモジュールのコマンド(エリアビットイメージ書き込み, 5.4.1.2節)に対応します．

###   void setDisplayStartAddress(word displayStartAddress)
表示スタートアドレスを指定します．
VFDモジュールのコマンド(表示スタートアドレス指定, 5.4.1.3節)に対応します．

###   void syncNextCommand()
このコマンドの後に書き込まれたコマンドは，内部表示リフレッシュに同期して動作します．
VFDモジュールのコマンド(リフレッシュ同期表示指定, 5.4.1.4節)に対応します．

###   void setBrightness(byte brightness)
輝度を設定します．
VFDモジュールのコマンド(表示輝度指定5.4.1.5節)に対応します．

### setDrawingAddress(word address)
show()メソッドで転送する先のVFDの表示メモリのアドレス
(描画用アドレス)を設定します．

### rotateDrawingAddress()
転送先アドレスが複数面ある場合にローテートします．
非表示エリアに描画するような場合に使用します．

### setDisplayStartAddressToDrawingAddress()
描画用アドレスの値を，VFDの表示アドレスに設定します．
非表示面に描画した後に表示開始するような場合に使用します．

###  void clear()
フレームバッファのクリア，VFD表示メモリのクリアを行います．
VFDの表示開始アドレスと描画用アドレスを0に設定します．

###  void clearFrameBuffer()
フレームバッファ(buf[])をクリアし，カーソル位置を(0,0)にします．
FrameBuffer::clear()と等価です．

###  void show()
buf[]の内容をVFDに転送します．
転送先の先頭アドレスは描画用アドレス(m_drawing_addr)です．
VFDに送られた内容はm_buf[]にもコピーされます．

graphicDMAモードにおいてもVFDへの転送はそれなりに時間がかかるので，
差分が含まれるエリア(差分が開始したところから終了したところまで)を転送します．

###  void rotateAndShow()
描画用アドレスをローテートした後に描画します．

###  void syncAndShow()
VFDの内部表示リフレッシュに同期してshow()のバッファ転送を行います．

###  void syncRotateAndShow()
描画用アドレスをローテートした後に描画し，
VFDの内部表示リフレッシュに同期して表示アドレスを更新します．

###  void showAllArea()
buf[]全体を(差分転送ではなく)VFDの表示メモリに転送します．

## private変数
###  byte *m_buf
VFDの表示メモリに転送した内容を保持するためのバッファです．
差分転送用に使用します．

###  bool m_first_show
1回目のshow()処理であることを示すフラグです．
- true:  buf[]全体をVFDに転送します．
- false: 差分転送を行います．

###  word m_disp_memsize
VFDモジュールの総バッファサイズ(byte数)(表示エリア+非表示エリア)です．

###  word m_disp_areasize
VFDモジュールの表示エリアのサイズ(byte数)です．

###  word m_drawing_addr
show()が転送する先の表示メモリのアドレスです．

###  word m_dad
VFDモジュールのアドレス(マニュアルでDADと呼ばれているもの)です．

## private関数
###  void flushCommandData()
コマンドの強制中断等によって，
writeBitImage()等の処理が途中で中断されている可能性があるため，
VFD初期化時に，
VFDに対して表示メモリサイズ分のダミーデータを送ります．

###  void writeCommand(byte command)
VFDモジュールのコマンドを起動します．
「基本機能ソフトウェア仕様書 5.4節」参照．
