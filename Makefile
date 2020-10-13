#-------------------------------------------------------------------------------
# <one line to give the program's name and a brief idea of what it does.>
# Copyright (C) 2020 Aamos Pernu
# 
# AamOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# AamOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this aamOS.  If not, see <https://www.gnu.org/licenses/>.
#-------------------------------------------------------------------------------
CC := i386-elf-gcc

AUXFILES := Makefile README.md COPYING

PROJDIRS := src

IMAGE := aamOS.img

all: dependencies $(IMAGE) dist

dependencies:
	make all -C src

clean:
	rm aamOS.elf aamOS.img aamOS.tar.gz
	make clean -C src
	
dist:
	mkdir aamOS
	cp -r $(AUXFILES) aamOS
	cp -r $(PROJDIRS) aamOS
	tar czf aamOS.tar.gz aamOS
	rm -rf aamOS
	
$(IMAGE): src/aamOS.bin
	/usr/local/bin/xorrisofs -o $(IMAGE) -J -R -V "AAMOS" -G src/aamOS.bin
	cp src/aamOS.elf aamOS.elf
