作成途中のドラフトです.(2021/3/10)

# Noritake Itron GU3000シリーズ VFDモジュール用Raspberry Piパラレルインターフェース説明書

## この文書について

この文書は，Noritake Itron GU3000シリーズ VFDモジュール用に作成したインターフェースについて説明するものです．
ノリタケ伊勢電子株式会社(以下，Noritake Itron)とは一切関係のない個人が開発したものです．

# 開発環境
## ハードウェア
- Noritake Itron GU256x128C-3100
- Raspbery Pi (4 および zero W)
- GU3000RasPiIF(レベル変換用インターフェース(自作))

## ソフトウェア(OS)
- Raspbery Pi Zero W
  - OS: Raspbian (Linux raspberrypi 5.4.79+ #1373)
- Raspberry Pi 4
  - OS: Raspbian (Linux raspberrypi 5.4.72-v7l+ #1356)

# 使用方法
## VFDモジュールDIPスイッチの設定 ★★★重要★★★
コマンドモード選択(SW1 No.6): ON グラフィックDMAモードに設定します．
(ソフトウェア仕様書 6.1.3 コマンドモード選択 参照)

## ラズベリーパイとVFDの接続
1. インターフェースボードをラズベリーパイのGPIOコネクタに接続
2. インターフェースボードとVFDをケーブルで接続
結線は下記のようになっています．
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
## 電源の接続

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
### ライブラリのbuild
```
git clone https://github.com/ryomuk/gu3000.git
cd gu3000/src
make
cd examples
./make.sh (もしくは，サブディレクトリでmake)
```

## サンプルプログラム
### test
簡単な描画と速度の測定．
```
cd gu3000/src/examples/test
make
./test
```
![](../images/test.jpg)

### fonttest
ライブラリに実装されたフォントの表示．
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
ワイヤーフレームモデルの描画．下記のサイトにいろいろなデータがあります．
https://people.sc.fsu.edu/~jburkardt/data/obj/obj.html
```
cd gu3000/src/examples/showwire
make
./showwire teapot.obj
```
↓クリックで動画再生  
[![](../images/teapot.jpg)](https://www.youtube.com/watch?v=gbkjLUjZCEo "showwire teapot.obj")

### lifegame
ライフゲーム(Conway's Game of Life)です．
```
cd gu3000/src/examples/lifegame
make
./lifegame
```
![](../images/lifegame.jpg)

### showbmp
bmpファイルを表示します．
```
cd gu3000/src/examples/showbmp
make
./showbmp 256128sample.bmp
```
![](../images/showbmp.jpg)

### viewtxt
テキストを表示します．フォントの選択ができます．
```
cd gu3000/src/examples/viewtxt
make
./viewtxt sample.txt
```
![](../images/viewtxt.jpg)

# コンソール画面，Xwindowについて
コンソール画面の表示や，Xwindowが起動できましたが，いろいろと試行錯誤してとりあえず出来たという感じなので，これが正しい方法かどうかは不明ですが，
とりあえず私がやったことをまとめておきます．

## /dev/fb0を利用した描画
Raspberry Piの/dev/fb0を逐次(50ms毎等)VFDにコピーすることによって，
コンソール画面やXwindowの画面を表示させることができます．
上に紹介したサンプルプログラム類を同時に走らせると画面のちらつきが発生したり，正しく描画できないことがあるのでご注意下さい．

下記方法は，HDMI出力を止めて/dev/fb0をVFDに表示するものです．
HDMIからの画面出力はできなくなりますので，
事前に，ssh等でリモートでログインできる環境を整えて下さい．

私は面倒なのであきらめましたが，HDMIと両立させる方法もあるかと思いますので，
両立させたい場合は適宜設定して下さい．

### console
### フレームバッファ/dev/fb0をVFDに表示するための設定
1. /dev/fb0 を作成 (HDMI出力は外す)
/boot/config.txtに以下を追加
```
framebuffer_height=128	
framebuffer_width=256
hdmi_cvt=256 128 60 3 0 0 0
hdmi_group=2
hdmi_mode=87
hdmi_force_hotplug=1
```

2. dev/fb0 をVFDに逐次表示するコマンド examples/showfb, examples/showfb.sh
を/usr/local/binにコピー．
それらコマンドをサービスとして起動するための設定．サービスを有効化．

```
cd gu3000/src/examples/showfb
make
sudo cp showfb /usr/local/bin/
sudo cp showfb.sh /usr/local/bin/
sudo cp showfb.service /etc/systemd/system/
sudo systemctrl enable showfb.service
```

無効化したい場合は，下記のコマンドを実行．
```
sudo systemctrl stop showfb.service
```

リブートすると，VFDにコンソール画面が表示されます．
![](../images/console.jpg)

### Xwindow
### Xorg用設定
gu3000/src/examples/showfb/xorg.confを/etc/X11/xorg.confにコピー．
ラズパイ標準のX環境は小画面ではほとんど使えないので，
小画面用のwindow manager(twm)を使う．
.xsessionをユーザのホームディレクトリに置く．
X用のフォントもインストールする．

```
cd gu3000/src/examples/showfb
sudo cp xorg.conf /etc/X11/
sudo apt install twm
sudo apt install xfonts-base
cp dot.xsession ~/.xsession
cp dot.twmrc ~/.twmrc
```

rebootしてコンソール画面で
```
startx
```
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
