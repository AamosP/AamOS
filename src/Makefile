CC := i386-elf-gcc
AS := i386-elf-as

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes

CFLAGS := -nostdlib -ffreestanding -g -std=gnu99 $(WARNINGS) -I. -mno-red-zone -mgeneral-regs-only
ASFLAGS := -nostdlib -Wall -I.

all: start.o kernel.o aamOS.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@

aamOS.elf: kernel.o vga.o utils.o keyboard.o font.o serial.o console.o interrupt_handler.o gdt.o idt.o
	$(CC) -ffreestanding -nostdlib -g -T link.ld $? start.s -o aamOS.elf -lgcc -mno-red-zone $(WARNINGS)