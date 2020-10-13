#!/bin/sh
./build.sh
/usr/local/bin/qemu-system-i386 -hda aamOS.img -s -S -vga vmware -serial tcp::1111,server,nowait -serial tcp::2222,server,nowait -serial tcp::3333,server,nowait -serial tcp::4444,server,nowait &
