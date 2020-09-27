#include <sys/mem.h>

void* memcpy(void* dest, const void* src, size_t n){
	char* dest_str = (char*) dest;
	char* src_str = (char*) src;

	int i;
	for(i = 0; i < n; i++)
		dest_str[i] = src_str[i];

	return dest;
}
