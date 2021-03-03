#!/bin/bash

ffmpeg -i Touhou_BadApplePV.mp4 -s 128x256 -pix_fmt monob -c:v rawvideo -f rawvideo -vf transpose=0 -an - | ./playbmp
