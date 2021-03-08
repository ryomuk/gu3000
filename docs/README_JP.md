##Noritake Itron GU3000シリーズ VFDモジュール用ライブラリマニュアル

### この文書について

この文書は，Noritake Itron GU3000シリーズ VFDモジュール用に作成したプログラムについて説明するものです．
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


### グラフィックDMAモード用ライブラリ
GU3000GraphicクラスはGU3000GPIOクラスとFrameBufferクラスを継承し，
グラフィックDMAモードのVFDにFrameBufferの内容を表示する機能を実装したものです．

### 概念図

描画はFrameBufferのbuf上に行われます．
buf[]はVFD::show()によってVFDのメモリdisplay_memory[]に転送されます．
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
|m_buf[WIDTH*HEITH*面数]
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
|  display_memory[WIDTH*HEITH*面数]
+--------------------------------
```

VFDモジュールDIPスイッチの設定 ※重要
コマンドモード選択(SW1 No.6): ON グラフィックDMAモードに設定します．
(ソフトウェア仕様書 6.1.3 コマンドモード選択 参照)


### VFDへの電源供給について

事前にインストールが必要なもの
wiringPi おそらくraspbianに標準でインストール済み
インストールされていない場合はインストール
% sudo apt install wiringpi

Xwindow関連(必要であれば)
```
sudo apt install xorg-dev
sudo apt install xvfb
sudo apt install xfonts-utils
sudo apt install xfont-base

sudo apt install ncurses-dev
```




### お手軽なテスト
(cdの引数は場所が明確になるようにgu3000から書いていますが，適当に読み替えて下さい)
```
cd gu3000/src
make
cd gu3000/src/examples
./make.sh
cd gu3000/src/examples/test
./test
```

### コンソール画面の表示


### Xwindowの表示


## おまけ
### ノーマルコマンドモード用ライブラリについて



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