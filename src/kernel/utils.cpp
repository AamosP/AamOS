/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>
#include <stdarg.h>

/* Convert the integer D to a string and save the string in BUF. If
 BASE is equal to ’d’, interpret that D is decimal, and if BASE is
 equal to ’x’, interpret that D is hexadecimal. */
void itoa(char *buf, int base, int d) {
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = (unsigned) d;
	int divisor = 10;

	/* If %d is specified and D is minus, put ‘-’ in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = (unsigned) -d;
	} else if (base == 'x') {
		divisor = 16;
	} else if (base == 'b') {
		divisor = 2;
	}
	/* Divide UD by DIVISOR until UD == 0. */
	do {
		uint32_t remainder = ud % (unsigned) divisor;

		*p++ =
				(char) ((remainder < 10) ?
						remainder + '0' : remainder + 'a' - 10);
	} while (ud /= (unsigned) divisor);

	/* Terminate BUF. */
	*p = 0;

	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}

void dump_struct(void *structure, size_t bytes){
//	char* list = (char*) structure;
//
//	vga_puts_hex((uint) structure);
//	vga_puts(": ");
//
//	int i;
//	for(i = 0; i < bytes; i++){
//		vga_putc_hex(list[i]);
//		vga_puts(" ");
//	}
//
	//vga_puts("\n");
}



