#define ASM_FILE 1

.set STACK_SIZE, 0x4000

.set AOUT_KLUDGE, 0

.set MAGIC, 0xe85250d6
.set ARCH, 0
.set TAG_ADDRESS, 2
.set TAG_OPTIONAL, 1
.set TAG_ENTRY_ADDRESS, 3
.set TAG_FRAMEBUFFER, 5
.set TAG_END, 0

.text
.globl start, _start

start:
_start:
	jmp multiboot_entry

	.align 8

multiboot_header:
    .long MAGIC
    .long ARCH
    .long multiboot_header_end - multiboot_header
	.long -(MAGIC + ARCH + (multiboot_header_end - multiboot_header))

//.ifndef __ELF__
//address_tag_start:
//        .short TAG_ADDRESS
//        .short TAG_OPTIONAL
//        .long address_tag_end - address_tag_start
        /*  header_addr */
//        .long   multiboot_header
        /*  load_addr */
//        .long   start
        /*  load_end_addr */
//        .long   _edata
        /*  bss_end_addr */
//        .long   _end
//address_tag_end:
//entry_address_tag_start:
//        .short TAG_ENTRY_ADDRESS
//        .short TAG_OPTIONAL
//        .long entry_address_tag_end - entry_address_tag_start
        /*  entry_addr */
//        .long multiboot_entry
//entry_address_tag_end:
//.endif /*  __ELF__ */
framebuffer_tag_start:
        .short TAG_FRAMEBUFFER
        .short TAG_OPTIONAL
        .long framebuffer_tag_end - framebuffer_tag_start
        .long 1024
        .long 768
        .long 32
framebuffer_tag_end:
        .short TAG_END
        //.short 0
        .long 8
multiboot_header_end:
multiboot_entry:
	movl $(stack + STACK_SIZE), %esp

	pushl $0
	popf

	pushl %ebx

	pushl %eax

	call kernel_main

	pushl $halt_message
	//call print

l:	hlt
	jmp l

halt_message:
	.asciz "Halted."

	.comm stack, STACK_SIZE
_edata:

.section .bss
_end:
