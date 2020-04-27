STACK_SIZE equ 0x4000

AOUT_KLUDGE equ 0
PG_ALIGN equ 1
MEM_INFO equ 2
VID_MODE equ 4

FLAGS equ PG_ALIGN | MEM_INFO | VID_MODE | AOUT_KLUDGE

MAGIC equ 0x1BADB002

section .multiboot
	align 4
multiboot_header:
	dd MAGIC
	dd FLAGS
	dd -(MAGIC + FLAGS)
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0
	dd 0
	dd 1024
	dd 768
	dd 32

section .bss
align 16
stack_bottom:
	resb STACK_SIZE
stack_top:

extern kernel_main

section .text
global start, _start
start:
_start:
	jmp multiboot_entry

multiboot_entry:
;	push 0x3f8
;	call init_serial
;	push '1'
;	call write_serial

	mov esp, stack_top

	push 0
	popf

	push ebx
	push eax
	call kernel_main

	hlt
	jmp $

gdt:
	dq 0x0000000000000000
	dq 0x00cf9a000000ffff
	dq 0x00cf92000000ffff
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

%macro ISR_NOERRCODE 1			; define a macro, taking one parameter
  global isr%1			; %1 accesses the first parameter.
  extern isr%1_handler
  isr%1:
	cli
	jmp isr%1_handler
%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  extern isr%1_handler
  isr%1:
	cli
	jmp isr%1_handler
%endmacro

; This macro creates a stub for an IRQ - the first parameter is
; the IRQ number, the second is the ISR number it is remapped to
%macro IRQ 1
  global irq%1
  extern irq%1_handler
  irq%1:
	cli
	call irq%1_handler
	sti
	iret
%endmacro

ISR_NOERRCODE  0
ISR_NOERRCODE  1
ISR_NOERRCODE  2
ISR_NOERRCODE  3
ISR_NOERRCODE  4
ISR_NOERRCODE  5
ISR_NOERRCODE  6
ISR_NOERRCODE  7
ISR_ERRCODE    8
ISR_NOERRCODE  9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

IRQ  0
IRQ  1
IRQ  2
IRQ  3
IRQ  4
IRQ  5
IRQ  6
IRQ  7
IRQ  8
IRQ  9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15

global loadIdt
loadIdt:
	mov eax, [esp + 4]
	lidt [eax]
	ret

