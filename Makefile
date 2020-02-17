CC := i386-elf-gcc

AUXFILES := Makefile .gitignore .git/ src/link.ld src/grub.cfg src/Makefile

PROJDIRS := src

DRIVER_SRC := $(DRIVERS)/*.c
DRIVER_HDR := $(DRIVERS)/*.h

LINKER := $(PROJDIRS)/link.ld
ASMFILES := $(PROJDIRS)/*.s
SRCFILES := $(PROJDIRS)/*.c $(DRIVER_SRC)
HDRFILES := $(PROJDIRS)/*.h $(DRIVER_HDR)

OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.s,%.o,$(ASMFILES))
TSTFILES := $(patsubst %.c,%_t,$(SRCFILES)) $(patsubst %.s,%_t,$(ASMFILES))

ALLFILES := $(AUXFILES) $(ASMFILES) $(SRCFILES) $(HDRFILES)

.PHONY: all clean dist check

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes

CFLAGS := -ffreestanding -g -std=gnu99 $(WARNINGS)

all: dependencies

dependencies:
	make all -C src

clean:
	rm -r src/isodir src/aamOS.elf src/*.o

dist:
	tar czf aamOS.tgz $(ALLFILES)