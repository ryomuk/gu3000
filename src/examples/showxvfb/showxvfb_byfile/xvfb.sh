#!/bin/bash

Xvfb :1 -screen 0 256x128x8 -pixdepths 1 -fbdir /tmp/fb -blackpixel 1 -whitepixel 0

#Xvfb :1 -screen 0 256x128x8 -pixdepths 1 -shmem -blackpixel 1 -whitepixel 0


export DISPLAY=:1
