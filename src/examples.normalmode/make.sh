#!/bin/bash

for i in * ; do
    if [ -d $i ]  ; then
	echo cd to $i
	pushd $i
	make
	popd
    fi
done
