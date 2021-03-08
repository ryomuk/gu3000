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
```
cd gu3000/src/examples/test
make
./test
```

### showwire
![](images/teapot.jpg)
[![showwire](images/teapot.jpg)](https://www.youtube.com/watch?v=gbkjLUjZCEo "showwire")
```
cd gu3000/src/examples/showwire
make
./showwire teapot.obj
```

