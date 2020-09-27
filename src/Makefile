AS := nasm
CXX := i386-elf-g++
OBJCOPY := i386-elf-objcopy

WARNINGS := -Wall -Wextra
INCLUDE := include
CFLAGS := -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -fno-rtti -nostdlib -g -I $(INCLUDE) $(WARNINGS)

SRCFILES := $(shell find kernel boot mm -name "*.cpp")
ASMFILES := $(shell find kernel boot mm -name "*.asm")
OBJFILES := $(patsubst %.asm,%.o,$(ASMFILES))

all: aamOS.bin

%.o: %.asm
	$(AS) -f elf32 $< -o $@

aamOS.bin: $(OBJFILES) $(SRCFILES)
	$(CXX) $(CFLAGS) -T linker.ld -o aamOS.elf $?
	$(OBJCOPY) -O binary aamOS.elf aamOS.bin
	
clean:
	rm $(OBJFILES) aamOS.bin aamOS.elf
