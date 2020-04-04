#!/bin/sh
outfile=aamOS.iso

make all
mkdir -p src/isodir/boot/grub
cp src/grub.cfg src/isodir/boot/grub/grub.cfg
cp src/aamOS.elf src/isodir/boot/aamOS.elf
if [[ "$OSTYPE" == "linux" ]] ; then
	grub2-mkrescue src/isodir -o aamOS.iso
elif [[ "$OSTYPE" == "darwin"* ]] ; then
	grub-mkrescue src/isodir -o aamOS.iso
fi
