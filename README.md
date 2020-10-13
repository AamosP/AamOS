# AamOS

AamOS is a hobby OS project written in C++ and is distributed under the terms of the GNU General Public License

AamOS stands for Aamos's amazing multiuser operating system

# Building

Clone the repository and change to its directory using:

<code>git clone https://github.com/AamosP/AamOS.git AamOS && cd AamOS</code>

Then build AamOS using:

<code>make all</code>

# Running

You can run AamOS in QEMU or Bochs:

<code>./run.sh [qemu|bochs] [debug]</code>

Calling run.sh without arguments will run AamOS using qemu without debug

If running with Bochs, the debug aregument doesn't need to be present

There is also a shortcut to running with QEMU in debug mode

<code>./rungdb.sh && gdb -ex "target remote localhost:1234" -ex "symbol-file aamOS.elf"</code>
