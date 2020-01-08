mkdir -p src/isodir/boot/grub
cp src/grub.cfg src/isodir/boot/grub/grub.cfg
cp src/aamOS.elf src/isodir/boot/aamOS.elf
i386-elf-grub-mkrescue src/isodir -o aamOS.iso
