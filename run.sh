#!/bin/sh
#*******************************************************************************
# Copyright (c) 2020 Aamos Pernu.
#*******************************************************************************
make all

if [[ "$1" == "qemu" ]] ; then
	if [[ "$2" == "debug" ]] ; then
		qemu-system-i386 -hda aamOS.iso -s -S &
		gdb --eval-command='target remote localhost:1234' --eval-command='symbol-file src/aamOS.elf'
	else
		qemu-system-i386 -hda aamOS.iso -serial stdio -m size=4096
	fi
elif [[ "$1" == "bochs" ]] ; then
	bochs -f bochsrc -q
else
	qemu-system-i386 -hda aamOS.iso -serial stdio -m size=4096
fi

make clean