#!/bin/bash

for i in Noritake6x8 4x6 H68TR MICRlike7x8 MICRlike6x6 16segments ; do
    echo $i
    ./font2txt -f $i > ${i}.txt
    rw-psf/writepsf ${i}.txt ${i}.psf
done
