# gu3000
日本語での説明は下記を参照して下さい．
- [docs/README_JP.md](docs/README_JP.md)
- [docs/LibraryManual.md](docs/LibraryManual.md)

![](images/showbmp.jpg)

Library for Noritake Itron GU3000 series (GU3100 and GU3900) VFD module parallel interface graphic DMA mode for Raspberry Pi

See documents in docs for further information.
(Most of them are in Japanese, but Google or DeepL will translate them.)

## Hardware configuration
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

## WringPi version
You need wringPi 2.52 or later for Raspberry Pi 4B.

## How to build
```
git clone https://github.com/ryomuk/gu3000.git
cd gu3000/src
make
cd examples
make (or cd to subdirectory and make)
```

## Examples
### test
Test and benchmark of basic drawing methods.
```
cd gu3000/src/examples/test
make
./test
```
![](images/test.jpg)

### fonttest
Show installed fonts.
```
cd gu3000/src/examples/fonttest
make
./fonttest
```

MICR(Magnetic Ink Character Recognition) like font.  
![](images/fonttest_MICR.jpg)

Hitachi H68/TR 7-segment LED console font.  
![](images/fonttest_H68TR.jpg)

### showwire
Show wire frame model.
Many object models are available from https://people.sc.fsu.edu/~jburkardt/data/obj/obj.html
```
cd gu3000/src/examples/showwire
make
./showwire teapot.obj
```
click image to play movie  
[![](images/teapot.jpg)](https://www.youtube.com/watch?v=gbkjLUjZCEo "showwire teapot.obj")

### lifegame
Conway's Game of Life.
```
cd gu3000/src/examples/lifegame
make
./lifegame
```
![](images/lifegame.jpg)

### playbmp
Play bitmap video data (rawvideo of ffmpeg).
```
cd gu3000/src/examples/playbmp
make
ffmpeg -i sample.mp4 -s 128x256 -pix_fmt monob -c:v rawvideo -f rawvideo -vf transpose=0 -an - | ./playbmp
or
./play.sh
```
Make rawvideo file and play. (for raspberry pi zero (low CPU power))
```
ffmpeg -i sample.mp4 -s 128x256 -pix_fmt monob -c:v rawvideo -f rawvideo -vf transpose=0 -an - > sample.bmp
or
./makebmp.sh
./playbmp sample.bmp
```

Click to play movie  
[![](images/badapple.jpg)](https://www.youtube.com/watch?v=wEan5ha9sWA "playbmp")

### showbmp
Show bmp file.
```
cd gu3000/src/examples/showbmp
make
./showbmp 256128sample.bmp
```
![](images/showbmp.jpg)

### viewtxt
View text file. Several fonts are available.
```
cd gu3000/src/examples/viewtxt
make
./viewtxt sample.txt
```
![](images/viewtxt.jpg)

### console
View console by copying /dev/fb0 to VFD.

![](images/console.jpg)

### Xwindow
Xwindow on the VFD module.

![](images/xeyes.jpg)

click image to play movie  
[![](images/badapple_onX.jpg)](https://www.youtube.com/watch?v=z8M9jezuZ1E "Bad Apple on Xwindow")
