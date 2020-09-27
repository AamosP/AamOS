CC := i386-elf-gcc

AUXFILES := Makefile README.md run.sh sym.sh KBlayouts.txt

PROJDIRS := src

all: dependencies aamOS.img

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
	
aamOS.img: src/aamOS.bin
	xorrisofs -o aamOS.img -R -J -V "AAMOS" -G src/aamOS.bin
