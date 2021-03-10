作成途中のドラフトです.(2021/3/10)

## Noritake Itron GU3000シリーズ VFDモジュール用Raspberry Piパラレルインターフェース説明書

### この文書について

この文書は，Noritake Itron GU3000シリーズ VFDモジュール用に作成したインターフェースについて説明するものです．
ノリタケ伊勢電子株式会社(以下，Noritake Itron)とは一切関係のない個人が開発したものです．

### 開発に用いたハードウェア
- Noritake Itron GU256x128C-3100
- Raspbery Pi (4 および zero W)
- GU3000RasPiIF(レベル変換用インターフェース(自作))

### 開発環境
- Raspbery Pi Zero W
  - OS: Raspbian (Linux raspberrypi 5.4.79+ #1373)
- Raspberry Pi 4
  - OS: Raspbian (Linux raspberrypi 5.4.72-v7l+ #1356)

#使い方

## ハードウェア
```
Raspberry Pi 4/ Zero/ Zero W
GPIO
18  19  20...27
^  
|   |   | ...|  3.3V
 Level converter 
|   |   | ...|  5.0V
    v   v    v
RDY WR_ D0...D7
VFD module
```

### VFDモジュールDIPスイッチの設定 *重要*
コマンドモード選択(SW1 No.6): ON グラフィックDMAモードに設定します．
(ソフトウェア仕様書 6.1.3 コマンドモード選択 参照)

### VFDへの電源供給について
電源: DC 5V (プラグ内径2.1mm/外径5.5mm, センタープラス)
VFDの最大消費電流(全画素点灯時)は1.1Aです．

基板上のピンヘッダにより、
GPIOの5VとVFD(インターフェースボードからの給電)の5Vを
接続することができます．
これにより、Raspberry PiにGPIO経由で給電することもできます．
その場合には、それにあわせて十分な容量の電源をご用意下さい．

逆に、GPIOからの給電でVFDを動作させることも出来ますが、
その場合もRaspberry Pi側の電源の容量を十分に確保して下さい．

Raspberry Pi側給電と、VFD(インターフェースボード)側の給電で
2つのACアダプタを使用する場合には、
GPIO_VCCとVFD_VCCを切り離して下さい．
接続した状態で2つのACアダプタを使用すると、電源が並列に接続されるため、
電位差による逆流によってACアダプタに悪影響を及ぼすおそれがあります．

![](../images/power.png)

## ソフトウェア
### 事前にインストールが必要なもの
wiringPi おそらくraspbianに標準でインストール済み．
インストールされていない場合はインストールして下さい．
```
sudo apt install wiringpi
```
## ライブラリのbuild
```
git clone https://github.com/ryomuk/gu3000.git
cd gu3000/src
make
cd examples
./make.sh (もしくは，サブディレクトリでmake)
```

## サンプルプログラム
### test
Test and benchmark of basic drawing methods.
```
cd gu3000/src/examples/test
make
./test
```
![](../images/test.jpg)

### fonttest
Show installed fonts.
```
cd gu3000/src/examples/fonttest
make
./fonttest
```

MICR(Magnetic Ink Character Recognition) like font.
![](../images/fonttest_MICR.jpg)

Hitachi H68/TR 7-segment LED console font.
![](../images/fonttest_H68TR.jpg)

### showwire
Show wire frame model.
Many object models are available from https://people.sc.fsu.edu/~jburkardt/data/obj/obj.html
```
cd gu3000/src/examples/showwire
make
./showwire teapot.obj
```
click image to play movie  
[![](../images/teapot.jpg)](https://www.youtube.com/watch?v=gbkjLUjZCEo "showwire teapot.obj")

### lifegame
Conway's Game of Life.
```
cd gu3000/src/examples/lifegame
make
./lifegame
```
![](../images/lifegame.jpg)

### showbmp
Show bmp file.
```
cd gu3000/src/examples/showbmp
make
./showbmp 256128sample.bmp
```
![](../images/showbmp.jpg)

### viewtxt
View text file. Several fonts are available.
```
cd gu3000/src/examples/viewtxt
make
./viewtxt sample.txt
```
![](../images/viewtxt.jpg)

### console
View console by copying /dev/fb0 to VFD.

![](../images/console.jpg)

### xwindow
Xwindow on the VFD module.

![](../images/xeyes.jpg)

## おまけ
### ノーマルコマンドモード用ライブラリについて
ノーマルコマンドモードは，描画処理をモジュール上のプロセッサで行うモードです．
DIPスイッチの切り替えが必要なのと，通信オーバヘッドが大きく遅いので，
対応するライブラリは途中まで作成して放置してあります．
```
gu3000normal.cpp
gu3000normal.h
examples.normalmode/
```

### ノーマルコマンド使用方法
コマンドモード選択(SW1 No.6): OFF ノーマルコマンドモードに設定します．
(ソフトウェア仕様書 6.1.3 コマンドモード選択 参照)

## 参考文献
Noritake Itronの下記サイトから現行品(GU3900B)の技術資料が入手可能です．
本プログラムで動作確認しているモジュールは旧製品のGU3100ですが，基本的な部分は同じようでした．

[https://www.noritake-itron.jp/products/module/gu-3000](https://www.noritake-itron.jp/products/module/gu-3000)
- 「ディスプレイモジュールハードウェア仕様書」DS-1604-000-04, 2015年6月1日改訂
- 「ディスプレイモジュール3900Bシリーズ"基本機能"ソフトウェア仕様書」DS-1600-0007-00, 2010年11月29日制定
- 「蛍光表示管モジュール「GU-3000 シリーズ モジュール」アプリケーションノート」
APF300 R1.72
