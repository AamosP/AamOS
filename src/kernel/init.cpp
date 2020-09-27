/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <idt.h>
#include <aamOS/kernel.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>

extern "C" void kmain() {
	init_serial(COM1);
	idt_init();
//	init_kheap();
//	paging_init();
//	outb(0x21,0xfd);
//	outb(0xa1,0xff);
	sti();
	kb_init();
	init_isrs();
//	timer_init();
	//time_init();
	while (1) {
	}
}
