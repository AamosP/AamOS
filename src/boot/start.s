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
addr:
	dd 0
magic:
	dd 0
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

h:	hlt
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

extern isr_handler
; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
	pusha			; Pushes edi, esi, ebp, esp, ebx, edx, edx, eax

	mov ax, ds		; Lower 16-bits of eax = ds.
	push eax		; save the data segment descriptor

	mov ax, 0x10		; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler

	pop eax			; reload the original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa			; Pops edi, esi, ebp...
	add esp, 8		; Cleans up the pushed error code and pushed ISR number
	sti
	iret			; pops 5 things at once, CS, EIP, EFLAGS, SS, and ESP

;extern irq_handler

; This is our common IRQ stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
;irq_common_stub:
;	pusha			; Pushes edi, esi, ebp, esp, ebx, edx, ecx, eax
;
;	mov ax, ds		; Lower 16 bits of eax = ds.
;	push eax		; save the data segment descriptor
;
;	mov ax, 0x10		; load the kernel data segment descriptor.
;	mov ds, ax
;	mov es, ax
;	mov fs, ax
;	mov gs, ax
;
;	call irq_handler
;
;	pop ebx			; reload the original data segment descriptor
;	mov ds, bx
;	mov es, bx
;	mov fs, bx
;	mov gs, bx
;
;	popa			; Pops edi, esi, ebp, esp, ebx, edx, ecx, eax
;	add esp, 8		; Cleans up the pushed error code and pushed IRS number
;	sti
;	iret			; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

global loadIdt
loadIdt:
	mov eax, [esp + 4]
	lidt [eax]
	ret

