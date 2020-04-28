/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#ifndef _MEMORY_H
#define _MEMORY_H

#include <sys/types.h>

void init_paging();
void enable_paging();
void switch_page(unsigned int* page_dir);
void map_page(unsigned int vpage, unsigned int ppage);
unsigned int* mk_page();
unsigned int* mk_page_dir();
void mmap_page(unsigned int* page, unsigned int vpage, unsigned int ppage);

#endif
