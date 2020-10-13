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
AS := /usr/local/bin/nasm
CXX := /usr/local/bin/i386-elf-g++
OBJCOPY := /usr/local/bin/i386-elf-objcopy
#PATH := $(PATH):

WARNINGS := -Wall -Wextra
INCLUDE := include
CFLAGS := -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -fno-rtti -nostdlib -g -I $(INCLUDE) $(WARNINGS)

SRCFILES := $(shell find kernel boot mm fs -name "*.cpp")
ASMFILES := $(shell find kernel boot mm fs -name "*.asm")
OBJFILES := $(patsubst %.asm,%.o,$(ASMFILES))

all: aamOS.bin

%.o: %.asm
	$(AS) -f elf32 $< -o $@

aamOS.bin: $(OBJFILES) $(SRCFILES)
	$(CXX) $(CFLAGS) -T linker.ld -o aamOS.elf $?
	$(OBJCOPY) -O binary aamOS.elf aamOS.bin
	
clean:
	rm $(OBJFILES) aamOS.bin aamOS.elf
