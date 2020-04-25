/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <memory.h>
#include <sys/types.h>

uint64_t pdpt[4] __attribute__((aligned(0x20)));

void setupPaging() {
	uint64_t pt[512] __attribute__((aligned(0x1000)));
	uint64_t pd[512] __attribute__((aligned(0x1000)));
	pdpt[0] = (uint64_t)&pd | 1;
	pd[0] = (uint64_t)&pt | 3;
	unsigned int i, address = 0;
	for(int i = 0; i < 512; i++) {
		pt[i] = address | 3;
		address = address + 0x1000;
	}
	__asm__("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4");
	__asm__("movl %0, %%cr3" :: "a"(&pdpt));
	__asm__("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0");
}
