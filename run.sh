#!/bin/sh
usage() {
	echo "Usage: run.sh --file <file> --emulator <emulator> [OPTIONS]"
	echo ""
	echo "Options:"
	echo "	-f | --file				OS disk image"
	echo ""
	echo "	-e | --emulator <qemu|vbox|kvm> 	Emulator to run OS in"
	echo "		'qemu' runs the OS in qemu"
	echo "		'vbox' runs the OS in virtual box"
	echo "		'kvm' runs the OS in kvm"
	echo ""
	echo "	-h | --help 				Display this help message"
	echo ""
}

while [ "$1" != "" ] ; do
	case $1 in
		-f | --file ) shift
					  file=$1
					  ;;
		-e | --emulator ) shift
						  emu=$1
						  ;;
		-h | --help ) usage
					  exit
					  ;;
		* ) usage
			exit 1
	esac
	shift
done

if [[ "$file" == "" ]] ; then
	echo "Missing required parameter --file"
	usage
	exit 1
fi

if [[ -f "$file" ]] ; then
	if [[ "$emu" == "" ]] ; then
		echo "Missing required parameter --emulator"
		usage
		exit 1
	fi

	if [[ "$emu" == "qemu" ]] ; then
		echo "Running in qemu..."
		qemu-system-i386 $file
	elif [[ "$emu" == "vbox" ]] ; then
		echo "Running in virtual box..."
	elif [[ "$emu" == "kvm" ]] ; then
		echo "Running in kvm..."
	fi
else
	echo "File" $file "not found (Did you remember to build?"
	usage
	exit 1
fi