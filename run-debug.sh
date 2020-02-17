#!/bin/sh
make
if [ "$UNAME" == "Linux" ] ; then
	./make-iso-linux.sh
elif [ "$UNAME" == "Darwin" ] ; then
	./make-iso-mac.sh
fi
qemu-system-i386 -s -S aamOS.iso &
gdb --eval-command='target remote localhost:1234' --eval-command='symbol-file src/aamOS.elf'
make clean
