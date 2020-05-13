STACK_SIZE equ 0x4000

AOUT_KLUDGE equ 0
PG_ALIGN equ 1
MEM_INFO equ 2
VID_MODE equ 4

FLAGS equ PG_ALIGN | MEM_INFO | AOUT_KLUDGE

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
  isr%1:
	cli
	push 0
	push %1
	jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
	cli
	push %1
	jmp isr_common_stub
%endmacro

; This macro creates a stub for an IRQ - the first parameter is
; the IRQ number, the second is the ISR number it is remapped to
%macro IRQ 2
  global irq%1
  irq%1:
	cli
	push 0
	push %2
	jmp irq_common_stub
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

IRQ  0, 32
IRQ  1, 33
IRQ  2, 34
IRQ  3, 35
IRQ  4, 36
IRQ  5, 37
IRQ  6, 38
IRQ  7, 39
IRQ  8, 40
IRQ  9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

extern irq_handler
global irq_common_stub
irq_common_stub:
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call irq_handler

	pop eax
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa
	add esp, 8
	sti
	iret

extern isr_handler
global isr_common_stub
isr_common_stub:
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler

	pop eax
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa
	add esp, 8
	sti
	iret

global loadIdt
loadIdt:
	mov eax, [esp + 4]
	lidt [eax]
	ret

