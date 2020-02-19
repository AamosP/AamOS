#!/bin/sh
make
if [[ "$OSTYPE" == "linux" ]] ; then
	./make-iso-linux.sh
elif [[ "$OSTYPE" == "darwin"* ]] ; then
	./make-iso-mac.sh
fi
qemu-system-i386 aamOS.iso
make clean
