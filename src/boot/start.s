STACK_SIZE equ 0x4000

AOUT_KLUDGE equ 0

MAGIC equ 0xe85250d6
ARCH equ 0
TAG_ADDRESS equ 2
TAG_OPTIONAL equ 1
TAG_ENTRY_ADDRESS equ 3
TAG_FRAMEBUFFER equ 5
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
        dw TAG_FRAMEBUFFER
        dw TAG_OPTIONAL
        dd framebuffer_tag_end - framebuffer_tag_start
        dd 1024
        dd 768
        dd 32
framebuffer_tag_end:
        dw TAG_END
        ;//.short 0
        dd 8
multiboot_header_end:
multiboot_entry:
	mov esp, stack_top

	push 0
	popf

	push ebx

	push eax

	call kernel_main

l:	hlt
	jmp l

stack_bottom:
	resb STACK_SIZE
stack_top:

%macro idt_entry 3
	dw  ((%1 shl 0x30) shr 0x30)	; the low part of the address
	dw   %2    					; selector
	db   0							; Has to be zero
	db   %3  						; type
	dw (%1 shr 0x10) 				; the high part of the address
%endmacro

global loadGdt
gdt:
gdt_null:
	dq 0x0000000000000000    ;/* NULL descriptor */
gdt_code:
    dq 0x00c09a00000007ff    ;/* 8Mb (code) */
gdt_data:
    dq 0x00c09200000007ff    ;/* 8Mb (data) */
gdt_temp:
    dq 0x0000000000000000    ;/* TEMPORARY - don't use */

    times 252 db 0           ;/* space for LDT's and TSS's etc */
gdt_end:
gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt
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
global load_idt
load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

extern irq0_handler
extern irq1_handler
extern irq2_handler
extern irq3_handler
extern irq4_handler
extern irq5_handler
extern irq6_handler
extern irq7_handler
extern irq8_handler
extern irq9_handler
extern irq10_handler
extern irq11_handler
extern irq12_handler
extern irq13_handler
extern irq14_handler
extern irq15_handler

irq0:
  pusha
  call irq0_handler
  popa
  iret

irq1:
  pusha
  call irq1_handler
  popa
  iret

irq2:
  pusha
  call irq2_handler
  popa
  iret

irq3:
  pusha
  call irq3_handler
  popa
  iret

irq4:
  pusha
  call irq4_handler
  popa
  iret

irq5:
  pusha
  call irq5_handler
  popa
  iret

irq6:
  pusha
  call irq6_handler
  popa
  iret

irq7:
  pusha
  call irq7_handler
  popa
  iret

irq8:
  pusha
  call irq8_handler
  popa
  iret

irq9:
  pusha
  call irq9_handler
  popa
  iret

irq10:
  pusha
  call irq10_handler
  popa
  iret

irq11:
  pusha
  call irq11_handler
  popa
  iret

irq12:
  pusha
  call irq12_handler
  popa
  iret

irq13:
  pusha
  call irq13_handler
  popa
  iret

irq14:
  pusha
  call irq14_handler
  popa
  iret

irq15:
  pusha
  call irq15_handler
  popa
  iret
_edata:

section .bss
_end:
