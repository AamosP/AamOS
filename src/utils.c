#include <system.h>

__inline uint8_t inb(uint16_t __port) {
	uint8_t _v;
	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
	return _v;
}

__inline void outb(uint16_t __port, uint8_t __value) {
	__asm__ __volatile__ ("outb %b0,%w1": :"a" (__value), "Nd" (__port));
}

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

int oct2bin(uint8_t *str, int size) {
	int n = 0;
	uint8_t *c = str;
	while (size-- > 0) {
		n *= 8;
		n += *c - '0';
		c++;
	}
	return n;
}

/*  Format a string and print it on the screen, just like the libc
 function printf. */
int printf(const char *format, ...) {
	char **arg = (char**) &format;
	int c;
	char buf[20];
	int n = 0;

	arg++;

	while ((c = *format++) != 0) {
		if (c != '%') {
			console_putchar(c);
			n++;
		}
		else {
			char *p, *p2;
			int pad0 = 0, pad = 0;

			c = *format++;
			if (c == '0') {
				pad0 = 1;
				c = *format++;
			}
			if (c >= '0' && c <= '9') {
				pad = c - '0';
				c = *format++;
			}
			switch (c) {
			case 'd':
			case 'u':
			case 'x':
				itoa(buf, c, *((int*) arg++));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";
				int i = 0;
				while(p[i]) {
					n++;
					i++;
				}
				string: for (p2 = p; *p2; p2++)
					;
				for (; p2 < p + pad; p2++)
					console_putchar(pad0 ? '0' : ' ');
				while (*p)
					console_putchar(*p++);
				break;

			default:
				console_putchar(*((int*) arg++));
				break;
			}
		}
	}
	return n;
}

inline uint32_t farpeekl(uint16_t sel, void* off)
{
    uint32_t ret;
    asm ( "push %%fs\n\t"
          "mov  %1, %%fs\n\t"
          "mov  %%fs:(%2), %0\n\t"
          "pop  %%fs"
          : "=r"(ret) : "g"(sel), "r"(off) );
    return ret;
}

inline void farpokeb(uint16_t sel, void* off, uint8_t v)
{
    asm ( "push %%fs\n\t"
          "mov  %0, %%fs\n\t"
          "movb %2, %%fs:(%1)\n\t"
          "pop %%fs"
          : : "g"(sel), "r"(off), "r"(v) );
    /* TODO: Should "memory" be in the clobber list here? */
}

inline void io_wait()
{
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    asm volatile ( "outb %%al, $0x80" : : "a"(0) );
    /* %%al instead of %0 makes no difference.  TODO: does the register need to be zeroed? */
}

void* memset(void* bufptr, int value, int size) {
	uint8_t* buf = (uint8_t*) bufptr;
	for (int i = 0; i < size; i++)
		buf[i] = (uint8_t) value;
	return bufptr;
}

int puts(const char* string) {
	return printf("%s", string);
}

void putch(const char ch) {
	console_putchar(ch);
}

int kerror(const char* str) {
	uint32_t tfg = fg_col;
	fg_col = RED;
	int r = printf("%s\n", str);
	fg_col = tfg;
	return r;
}
