#include <utils.h>

__inline unsigned char inb(unsigned short int __port) {
	unsigned char _v;
	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
	return _v;
}

__inline void outb(unsigned char __value, unsigned short int __port) {
	__asm__ __volatile__ ("outb %b0,%w1": :"a" (__value), "Nd" (__port));
}

/* Convert the integer D to a string and save the string in BUF. If
 BASE is equal to ’d’, interpret that D is decimal, and if BASE is
 equal to ’x’, interpret that D is hexadecimal. */
void itoa(char *buf, int base, int d) {
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put ‘-’ in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x') {
		divisor = 16;
	} else if(base == 'b') {
		divisor = 2;
	}
	/* Divide UD by DIVISOR until UD == 0. */
	do {
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);

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
