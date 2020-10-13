;-------------------------------------------------------------------------------
; <one line to give the program's name and a brief idea of what it does.>
; Copyright (C) 2020 Aamos Pernu
; 
; AamOS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; AamOS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this aamOS.  If not, see <https://www.gnu.org/licenses/>.
;-------------------------------------------------------------------------------

section .boot
bits 16

BLACK equ 0x0
BLUE equ 0x1
GREEN equ 0x2
CYAN equ 0x3
DARK_RED equ 0x4
PURPLE equ 0x5
BROWN equ 0x6
LIGHT_GRAY equ 0x7
GRAY equ 0x8
LIGHT_BLUE equ 0x9
LIME equ 0xa
LIGHT_CYAN equ 0xb
RED equ 0xc
MAGENTA equ 0xd
YELLOW equ 0xe
WHITE equ 0xf

%define parseColor(bg,fg) ((bg << 12) | (fg << 8))

%imacro Print_16 1
	mov si,%1
	mov ah,0x0e
.loop:
    lodsb
    or al,al
    jz p16end
    int 0x10
    jmp .loop
p16end:
%endmacro

%imacro Print_32 2
	mov esi,%1
	mov ebx,0xb8000
.loop:
    lodsb
    or al,al
    jz p32end
    or eax,%2
    mov word [ebx],ax
    add ebx,2
    jmp .loop
p32end:
%endmacro

global boot
boot:
    ;call Print_16 hello
	;xchg bx,bx

    mov ax,0x2401
    int 0x15 ; enable A20 bit

	xchg bx,bx

	mov ax,0x3
	int 0x10

	push ebx

    mov [disk],dl
	mov ah, 0x2
	mov al, 64
	mov ch, 0
	mov dh, 0
	mov cl, 2
	mov dl, [disk]
	mov bx, c0_h0_s2
	int 0x13

	pop ebx
	;cli
	;hlt
	;extern paging_init
	cli
	lgdt [gdt_pointer]
	mov eax,cr0
	or eax,0x1
	mov cr0,eax
	mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
	jmp CODE_SEG:boot2
gdt_start:
    dw 0,0,0,0
gdt_code:
    dw 0xFFFF
    dw 0x0000
    dw 0x9a00
    dw 0x00C0
gdt_data:
    dw 0xFFFF
    dw 0x0000
    dw 0x9200
    dw 0x00C0
gdt_null:
	dw 0,0,0,0
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start
	dd gdt_start
disk:
	db 0x0
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
times 510 - ($-$$) db 0
dw 0xaa55
c0_h0_s2:
bits 32
;hello: db "Hello",0
boot2:
	;Print_32 hello, parseColor(BLACK,WHITE)
	mov esp,kernel_stack_top
	;xchg bx,bx
	extern kmain
	call kmain
	cli
	hlt

section .bss
align 4
kernel_stack_bottom: equ $
    resb 16384 ; 16 KB
kernel_stack_top:
