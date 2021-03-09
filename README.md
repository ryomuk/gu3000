# gu3000
Library for Noritake Itron GU3000 series VFD module for Raspberry pi 4 and zero

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

## How to build
```
git clone https://github.com/ryomuk/gu3000.git
cd gu3000/src
make
cd examples
./make.sh (or cd to subdirectory and make)
```

## Examples
### test
![](images/test.jpg)
```
cd gu3000/src/examples/test
make
./test
```
Test and benchmark of basic drawing methods.

### fonttest
![](images/fonttest_MICR.jpg)
![](images/fonttest_H68TR.jpg)
```
cd gu3000/src/examples/fonttest
make
./fonttest
```
Show installed fonts.

### showwire
click image to play movie
[![](images/teapot.jpg)](https://www.youtube.com/watch?v=gbkjLUjZCEo "showwire teapot.obj")
```
cd gu3000/src/examples/showwire
make
./showwire teapot.obj
```

### lifegame
![](images/lifegame.jpg)
```
cd gu3000/src/examples/lifegame
make
./lifegame
```
Conway's Game of Life.

### showbmp
![](images/lifegame.jpg)
```
cd gu3000/src/examples/showbmp
make
./showbmp 256128sample.bmp
```
Show bmp file.

### viewtxt
![](images/viewtxt.jpg)
```
cd gu3000/src/examples/viewtxt
make
./viewtxt sample.txt
```
View text file. Several fonts are available.




