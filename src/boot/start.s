STACK_SIZE equ 0x4000

AOUT_KLUDGE equ 0

MAGIC equ 0xe85250d6
ARCH equ 0

TAG_FB equ 5
TAG_OPTIONAL equ 1
TAG_END equ 0

extern kernel_main

section .text
global start, _start
start:
_start:
	jmp multiboot_entry

	align 8
multiboot_header:
	dd MAGIC
	dd ARCH
	dd multiboot_header_end - multiboot_header
	dd -(MAGIC + ARCH + (multiboot_header_end - multiboot_header))
framebuffer_tag_start:
	dw TAG_FB
	dw TAG_OPTIONAL
	dd framebuffer_tag_end - framebuffer_tag_start
	dd 1024
	dd 768
	dd 32
framebuffer_tag_end:
	dw TAG_END
	;dw 0
	dd 8
multiboot_header_end:
multiboot_entry:
	mov esp, stack_top

	push 0
	popf

	push ebx
	push eax

	call kernel_main

	hlt
	jmp $

stack_bottom:
	resb STACK_SIZE
stack_top:

gdt:
	dq 0x0000000000000000
	dq 0x00c09a00000007ff
	dq 0x00c09200000007ff
	dq 0x0000000000000000
gdt_end:
gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt
global loadGdt
loadGdt:
	cli
	lgdt [gdt_desc]
	jmp 0x08:reload_CS
reload_CS:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret

global loadIdt
loadIdt:
	mov eax, [esp + 4]
	lidt [eax]
	ret

extern irq0_handler,irq1_handler,irq2_handler,irq3_handler,irq4_handler,irq5_handler,irq6_handler,irq7_handler,irq8_handler,irq9_handler,irq10_handler,irq11_handler,irq12_handler,irq13_handler,irq14_handler,irq15_handler
global irq0,irq1,irq2,irq3,irq4,irq5,irq6,irq7,irq8,irq9,irq10,irq11,irq12,irq13,irq14,irq15
irq0:
	call irq0_handler
	iret
irq1:
	call irq1_handler
	iret
irq2:
	call irq2_handler
	iret
irq3:
	call irq3_handler
	iret
irq4:
	call irq4_handler
	iret
irq5:
	call irq5_handler
	iret
irq6:
	call irq6_handler
	iret
irq7:
	call irq7_handler
	iret
irq8:
	call irq8_handler
	iret
irq9:
	call irq9_handler
	iret
irq10:
	call irq10_handler
	iret
irq11:
	call irq11_handler
	iret
irq12:
	call irq12_handler
	iret
irq13:
	call irq13_handler
	iret
irq14:
	call irq14_handler
	iret
irq15:
	call irq15_handler
	iret
