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
outfile=aamOS.iso

make all
mkdir -p src/isodir/boot/grub
cp src/grub.cfg src/isodir/boot/grub/grub.cfg
cp src/aamOS.elf src/isodir/boot/aamOS.elf
if [[ "$OSTYPE" == "linux" ]] ; then
	grub2-mkrescue src/isodir -o aamOS.iso
elif [[ "$OSTYPE" == "darwin"* ]] ; then
	grub-mkrescue src/isodir -o aamOS.iso
fi
