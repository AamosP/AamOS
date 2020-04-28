/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>
#include <multiboot.h>
#include <sys/types.h>
#include <stdio.h>
#include <asm/system.h>
#include <asm/io.h>
#include <memory.h>
#include <time.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

extern void idt_init(void);
extern void loadGdt(void);
void kernel_main(unsigned long magic, unsigned long addr);

void kernel_main(unsigned long magic, unsigned long addr) {
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC)return;
	multiboot_info_t *mbi;
	mbi = (multiboot_info_t*)addr;
	VGA_init(mbi);
	console_init(mbi, WHITE, BLACK);
	init_serial(COM1);
	loadGdt();
	idt_init();
	sti();
	init_isrs();
	kb_init();
	time_init();
	timer_init();
	init_paging();
//	enable_paging();
//	switch_page((uint32_t*)0xffff0000);
//	mmap_page(mk_page_dir(), 0xffff0000, 0xfd000000);
//	*((uint32_t*)0xffff0000) = 0x00ffffff;
}
