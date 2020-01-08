#!/bin/sh
make
if [ "$UNAME" == "Linux" ] ; then
	./make-iso-linux.sh
elif [ "$UNAME" != "Linux" ] ; then
	./make-iso-mac.sh
fi
qemu-system-i386 -cdrom aamOS.iso
make clean