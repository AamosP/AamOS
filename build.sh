#!/bin/sh

usage() {
	echo "Usage: run.sh --type <type> [OPTIONS]"
	echo ""
	echo "Options:"
	echo "	-t | --type <live-usb|installer>	Output image type"
	echo "		'live-usb' outputs the OS to 'outfile'(defined by -o)"
	echo "		'installer' outputs OS installer to 'outfile'(Not implemented yet"
	echo ""
	echo "	-o | --outfile filename			Outfile (preferably an iso image)"
	echo ""
	echo "	-h | --help				Display this help message"
	echo ""
}

outfile=aamOS.iso
while [ "$1" != "" ] ; do
	case $1 in
		-o | --outfile ) shift
						 outfile=$1
						 ;;
		-t | --type ) shift
					  type=$1
					  ;;
		-h | --help ) usage
					  exit
					  ;;
		* ) usage
			exit 1
	esac
	shift
done

if [[ "$type" == "" ]] ; then
	echo "Missing required parameter --type"
	usage
	exit 1
fi

if [[ "$type" == "live-usb" ]] ; then
	make
	echo "Making live-usb image..."
	echo "Making /boot/grub directory..."
	mkdir -p src/isodir/boot/grub
	echo "Copying grub.cfg to /boot/grub/grub.cfg..."
	cp src/grub.cfg src/isodir/boot/grub/grub.cfg
	echo "Copying aamOS.elf to /boot/aamOS.elf..."
	cp src/aamOS.elf src/isodir/boot/aamOS.elf
	echo "Creating" $outfile
	if [[ "$OSTYPE" == "linux" ]] ; then
		grub2-mkrescue src/isodir -o $outfile
	elif [[ "$OSTYPE" == "darwin"* ]] ; then
		i386-elf-grub-mkrescue src/isodir -o $outfile
	fi
elif [[ "$type" == "installer" ]] ; then
	echo "Installer not implemented yet"
else
	echo "Invalid type"
	usage
	exit 1
fi