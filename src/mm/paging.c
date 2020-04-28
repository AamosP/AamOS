#include <sys/types.h>
#include <asm/system.h>
#include <memory.h>

#define PAGE_S 0x400000

uint32_t *curdir = 0;
uint32_t *lastpage = 0;
uint32_t *rootdir = 0;
uint32_t pdloc = 0;

void map_page(uint32_t virt, uint32_t phys) {
	uint32_t pti = virt >> 22;
	unsigned int i;
	for (i = 0; i < 1024; i++) {
		lastpage[i] = phys | 3;
		phys += 0x1000;
	}
	curdir[pti] = ((uint32_t) lastpage) | 3;
}

void enable_paging() {
	__asm__("mov %0, %%cr3"::"a"(&curdir[0]));
	__asm__("mov %cr0, %eax");
	__asm__("orl $0x80000001, %eax");
	__asm__("mov %eax, %cr0");
}

void switch_page(uint32_t *pd) {
	curdir = pd;
	if (pd != rootdir) {
		cli();
		hlt();
	}
	__asm__("mov %0, %%cr3"::"r"(&pd[0]));
	__asm__("mov %cr0, %eax; orl $0x80000001, %eax; mov %eax, %cr0");
}

void init_paging() {
	curdir = (uint32_t*) PAGE_S;
	pdloc = (uint32_t) curdir;
	lastpage = (uint32_t*) (PAGE_S + 0x1000);
	rootdir = curdir;

	uint32_t i;
	for (i = 0; i < 1024; i++) {
		curdir[i] = 3;
	}
	for (i = 0xff000000; i < 0xffff0000; i += PAGE_S) {
		map_page(i, i);
	}
	cli();
	switch_page(rootdir);
}

uint32_t* mk_page() {
	uint32_t *page;
	uint32_t i;
	for (i = 0; i < 1024; i++) {
		page[i] = 2;
	}
	return page;
}

uint32_t* mk_page_dir(){
	uint32_t* dir;
	uint32_t i;
	for(i = 0; i < 1024; i++){
		dir[i] =  2;
	}
	return (uint32_t*) dir;
}

void mmap_page(uint32_t *pd, uint32_t v, uint32_t p) {
	uint32_t pti = v >> 22;
	uint32_t *page = mk_page();

	uint32_t i;
	for (i = 0; i < 1024; i++) {
		page[i] = p | 3;
		p += 0x1000;
	}
	pd[pti] = ((uint32_t) page) | 3;
}
