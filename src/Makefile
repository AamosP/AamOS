CC := i386-elf-gcc

ASMFILES := $(shell find -type f -name "\*.s")
SRCFILES := $(shell find -type f -name "\*.c")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) OBJFILES := $(patsubst %.s,%.o,$(ASMFILES))

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes

CFLAGS := -ffreestanding -g -std=gnu99 $(WARNINGS) -I.
ASFLAGS := -g -std=gnu99 $(WARNINGS) -I.

all: start.o kernel.o aamOS.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(ASFLAGS) -c $< -o $@

aamOS.elf: start.o kernel.o
	$(CC) -ffreestanding -nostdlib -g -T link.ld $? -o aamOS.elf -lgcc