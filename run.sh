#!/bin/sh
./build.sh

if [[ "$1" == "debug" ]] ; then
	qemu-system-i386 -S -s -nographic aamOS.iso &
	gdb --eval-command='target remote localhost:1234' --eval-command='symbol-file src/aamOS.elf'
	exit
fi

qemu-system-i386 aamOS.iso -serial stdio

make clean