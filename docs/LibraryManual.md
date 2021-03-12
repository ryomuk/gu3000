# グラフィックDMAモード用ライブラリ
# 概念図

描画はFrameBufferのbuf上に行われます．
buf[]はVFD::show()によってVFDの表示メモリ(display_memory[])に転送されます．
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

### void GU3000GPIO::init(int rdy, int wr, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7)

### void GU3000GPIO::writeByte(byte byteData)

### void GU3000GPIO::setBitmapOrder(int order)

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





## GU3000Graphicクラス
GU3000GraphicクラスはGU3000GPIOクラスとFrameBufferクラスを継承し，
グラフィックDMAモードのVFDにFrameBufferの内容を表示する機能を実装したものです．

###

