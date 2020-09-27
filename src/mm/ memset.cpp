#include <sys/mem.h>

void* memset(void* s, int c, size_t n){
	char* str = (char*) s;

	int i;
	for(i = 0; i < n; i++)
		str[i] = (char) c;

	return s;
}
