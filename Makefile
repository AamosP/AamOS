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

all: dependencies

dependencies:
	make all -C src

clean:
	make clean -C src

dist:
	tar czf aamOS.tgz $(ALLFILES)