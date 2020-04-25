CC := gcc
AS := nasm
CC86 := i386-elf-gcc

WARNINGS := -Wall -Wextra

CFLAGS := -nostdlib -O2 -ffreestanding -g -std=gnu99 -Iinclude -nostdinc $(WARNINGS)

SRCFILES := $(shell find kernel boot mm -name "*.c")
ASMFILES := $(shell find kernel boot mm -name "*.s")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.s,%.o,$(ASMFILES))

all: $(OBJFILES) aamOS.elf

%.o: %.c
	$(CC86) $(CFLAGS) -c $< -o $@

#boot/start.o: boot/start.s
#	$(AS) -f elf32 $< -o $@
#
#boot/idt.o: boot/idt.c
#	$(CC86) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) -f elf32 $< -o $@

aamOS.elf: $(OBJFILES)
	$(CC86) $(WARNINGS) -ffreestanding -nostdlib -I. -T link.ld -o aamOS.elf $?
	
clean:
	rm $(OBJFILES) aamOS.elf