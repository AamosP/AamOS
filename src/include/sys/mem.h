#ifndef _MEM_H_
#define _MEM_H_

#include <sys/types.h>

void* memset(void* s, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);

#endif
