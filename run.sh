#!/bin/sh
make all -C src
cp src/aamOS.elf ./aamOS.elf

if [[ $1 == "qemu" ]]
then
	if [[ $2 == "debug" ]]
	then
		qemu-system-x86_64 -fda aamOS.img -s -S -m 4096 --vga vmware &
		gdb --eval-command="target remote localhost:1234" --eval-command="symbol-file aamOS.elf"
	else
		qemu-system-x86_64 -fda aamOS.img -serial stdio -m 4096 --vga vmware
	fi		
elif [[ $1 == "bochs" ]]
then
	./sym.sh aamOS.elf
	open -a Terminal -n
	bochs -f bochsrc.txt -q
	#'boot: floppy' 'floppya: 1_44=aamOS.img, status=inserted' 'magic_break: enabled=1'
else
	qemu-system-x86_64 -fda aamOS.img -serial stdio -m 4096 --vga vmware
fi

make clean -C src