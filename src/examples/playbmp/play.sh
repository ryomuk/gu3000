#!/bin/bash

#MOVIEFILE=Touhou_BadApplePV.mp4
MOVIEFILE=sample.mp4

ffmpeg -i $MOVIEFILE -s 128x256 -pix_fmt monob -c:v rawvideo -f rawvideo -vf transpose=0 -an - | ./playbmp -v
