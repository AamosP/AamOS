#!/bin/sh
./build.sh

qemu-system-i386 -hda aamOS.iso -serial stdio

make clean