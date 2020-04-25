#!/bin/sh
#*******************************************************************************
# Copyright (c) 2020 IBM Corporation and others.
#
# This program and the accompanying materials
# are made available under the terms of the Eclipse Public License 2.0
# which accompanies this distribution, and is available at
# https://www.eclipse.org/legal/epl-2.0/
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#     IBM Corporation - initial API and implementation
#*******************************************************************************
./build.sh

if [[ "$1" == "qemu" ]] ; then
	if [[ "$2" == "debug" ]] ; then
		qemu-system-i386 -hda aamOS.iso -s -S &
		gdb --eval-command='target remote localhost:1234' --eval-command='symbol-file src/aamOS.elf'
	else
		qemu-system-i386 -hda aamOS.iso -serial stdio -m size=4096
	fi
elif [[ "$1" == "bochs" ]] ; then
	bochs -f bochsrc -q
else
	qemu-system-i386 -hda aamOS.iso -serial stdio -m size=4096
fi

make clean