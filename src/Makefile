CC := i386-elf-gcc
AS := nasm

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes

CFLAGS := -nostdlib -O2 -ffreestanding -g -std=gnu99 -I. $(WARNINGS)
ASFLAGS := -nostdlib -g -I. -O2

SRCFILES := console.c font.c kernel.c serial.c utils.c vga.c idt.c irq.c
ASMFILES := start.s
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.s,%.o,$(ASMFILES))

all: aamOS.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) -f elf32 $< -o $@

aamOS.elf: $(OBJFILES)
	$(CC) $(WARNINGS) -ffreestanding -nostdlib -I. -T link.ld -o aamOS.elf $?