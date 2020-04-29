CC := i386-elf-gcc

AUXFILES := Makefile README.md run.sh

PROJDIRS := src

all: dependencies aamOS.iso clean

dependencies:
	make all -C src

clean:
	rm -rf isodir
	make clean -C src
	
dist:
	mkdir aamOS
	cp -r $(AUXFILES) aamOS
	cp -r $(PROJDIRS) aamOS
	tar czf aamOS.tar.gz aamOS
	rm -rf aamOS
	
aamOS.iso: src/aamOS.elf src/grub.cfg
	mkdir -p isodir/boot/grub
	cp src/grub.cfg isodir/boot/grub/grub.cfg
	cp src/aamOS.elf isodir/boot/aamOS.elf
	grub-mkrescue isodir -o aamOS.iso
