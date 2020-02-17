.extern kernel_main
.extern mbi
.extern idt

.set ALIGN, 1 << 0
.set MEMINFO, 1 << 1
.set VIDINFO, 1 << 2
.set FLAGS, ALIGN | MEMINFO | VIDINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
		.align 4
        .long MAGIC
        .long FLAGS
        .long CHECKSUM
        .long 0, 0, 0, 0, 0
        .long 0
        .long 800, 600, 32

.section .bss
	.align 16
	stack_bottom:
		.skip 16384
	stack_top:

.section .text
.global _start, storeIdt
.type _start, @function
.type storeIdt, @function

_start:
	mov $stack_top, %esp
	mov %ebx, mbi
	call kernel_main
	cli
l:	hlt
	jmp l

storeIdt:
	sidt idt
	ret

.size _start, .- _start
