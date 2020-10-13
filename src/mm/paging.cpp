/*******************************************************************************
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2020 Aamos Pernu
 * 
 * AamOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AamOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this aamOS.  If not, see <https://www.gnu.org/licenses/>.
 ******************************************************************************/
#include <paging.h>
#include <stdio.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void init_pd() {
	//set each entry to not present
	int i;
	for (i = 0; i < 1024; i++) {
		// This sets the following flags to the pages:
		//   Supervisor: Only kernel-mode can access them
		//   Write Enabled: It can be both read from and written to
		//   Not Present: The page table is not present
		page_directory[i] = 0x00000002;
	}
}

uint32_t* init_pt(uint32_t n) {
	uint32_t pt[1024] __attribute__((aligned(4096)));
	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	uint32_t i;
	//we will fill all 1024 entries in the table, mapping 4 megabytes
	for (i = 0; i < 1024; i++) {
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		pt[i] = 0; // attributes: supervisor level, read/write, present.
	}
	page_directory[n] = ((uint32_t) pt);
	//return pt;
	//page_directory[n] = ((uint32_t)pt) | 3;
}

void init_first_pt() {
	idpaging(first_page_table, 0, 0x400000);
	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	uint32_t i;
	//we will fill all 1024 entries in the table, mapping 4 megabytes
	for (i = 0; i < 1024; i++) {
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		first_page_table[i] |= 3; // attributes: supervisor level, read/write, present.
	}
	//page_directory[0] = ((uint32_t) first_page_table) | 3;
}

void load_page_directory(uint32_t* pd) {
	__asm__ __volatile__("mov %%cr3,%0"::"r"(pd));
}

void enable_paging() {
	__asm__ __volatile__("mov %eax,%cr0");
	__asm__ __volatile__("or %eax,0x80000000");
	__asm__ __volatile__("mov %cr0,%eax");
}

void init_paging() {
	init_pd();
	init_first_pt();
	idpaging(first_page_table, 0, 0x400000);
	page_directory[0] = ((unsigned int) first_page_table) | 3; // attributes: supervisor level, read/write, present
	load_page_directory(page_directory);
	enable_paging();
}

void idpaging(uint32_t *first_pte, vaddr_t from, int size) {
	from = from & 0xfffff000; // discard bits we don't want
	for (; size > 0; from += 4096, size -= 4096, first_pte++) {
		*first_pte = from | 1;     // mark page present.
	}
}

void * get_physaddr(void * virtualaddr)
{
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

    if(!(page_directory[pdindex] & 1))return NULL;

    unsigned long * pt = ((unsigned long *)page_directory[pdindex]);
    if(!((pt[ptindex] & 1)))return NULL;

    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}

void map_page(void* physaddr, void* virtualaddr, uint32_t flags) {
	uint32_t pdindex = (uint32_t)virtualaddr >> 22;
	uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03ff;
	if(!(page_directory[pdindex] & 1)) {
		init_pt(pdindex);
	}
	uint32_t* pt = ((uint32_t*)page_directory[pdindex]);
	if((pt[ptindex] & 1)) {
		printf("Page already present\n");
		return;
	}
	pt[ptindex] = ((uint32_t)physaddr) | (flags & 0xfff) | 0x01;
}

void page_fault(registers_t* regs) {
	printf("US RW P\n%i  %i  %i\n", regs->err_code & 1, (regs->err_code >> 1) & 1, (regs->err_code >> 2) & 1);
}
