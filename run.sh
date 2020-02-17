#!/bin/sh
make
if [ "$UNAME" == "Linux" ] ; then
	./make-iso-linux.sh
elif [ "$UNAME" == "Darwin" ] ; then
	./make-iso-mac.sh
fi
qemu-system-i386 aamOS.iso
make clean
