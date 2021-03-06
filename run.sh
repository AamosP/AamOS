if [ "$1" = "qemu" ]
then
	if [ "$2" = "debug" ]
	then
		./rungdb.sh && gdb -ex "target remote localhost:1234" -ex "symbol-file aamOS.elf"
	else	
		qemu-system-i386 -hda aamOS.img -vga vmware -serial tcp::1111,server,nowait -serial tcp::2222,server,nowait -serial tcp::3333,server,nowait -serial tcp::4444,server,nowait
	fi
elif [ "$1" = "bochs" ]
then
	./sym.sh aamOS.elf
	bochs -q -f bochsrc.txt
else
	qemu-system-i386 -hda aamOS.img -vga vmware -serial tcp::1111,server,nowait -serial tcp::2222,server,nowait -serial tcp::3333,server,nowait -serial tcp::4444,server,nowait
fi
