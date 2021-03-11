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
