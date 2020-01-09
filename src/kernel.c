#include <multiboot.h>
#include <stdint.h>

/* Macros. */

/* Check if the bit BIT in FLAGS is set. */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

/* Some screen stuff. */
/* The number of columns. */
#define COLUMNS                 80
/* The number of lines. */
#define LINES                   24
/* The attribute of an character. */
#define ATTRIBUTE               7
/* The video memory address. */
#define VIDEO                   0xB8000

/* Variables. */
/* Save the X position. */
static int xpos;
/* Save the Y position. */
static int ypos;
/* Point to the video memory. */
static volatile unsigned char *video;

/* Forward declarations. */
void kernel_main();
static void cls(void);
static void itoa(char *buf, int base, int d);
static void putchar(int c);
void printf(const char *format, ...);

multiboot_info_t *mbi;

void putpixel(multiboot_uint32_t fb, int x, int y, int bpp, int pitch,
		multiboot_uint32_t color) {
	multiboot_uint32_t *pixel = fb + y * pitch + x * (bpp / 8);
	switch (bpp) {
	case 8:
		*pixel = color;
		break;
	case 15:
	case 16:
		*pixel = color;
		break;
	case 24:
		*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
		break;
	case 32:
		*pixel = color;
		break;
	}
}

void fillrect(multiboot_uint32_t fb, int x, int y, int w, int h, int bpp,
		int pitch, multiboot_uint32_t color) {
	switch (bpp) {
	case 8:
		for (int j = y; j < y + h; j++) {
			for (int i = x; i < x + w; i++) {
				multiboot_uint32_t *pixel = fb + j * pitch + i * (bpp / 8);
				*pixel = color;
			}
		}
		break;
	case 15:
	case 16:
		for (int j = y; j < y + h; j++) {
			for (int i = x; i < x + w; i++) {
				multiboot_uint32_t *pixel = fb + j * pitch + i * (bpp / 8);
				*pixel = color;
			}
		}
		break;
	case 24:
		for (int j = y; j < y + h; j++) {
			for (int i = x; i < x + w; i++) {
				multiboot_uint32_t *pixel = fb + j * pitch + i * (bpp / 8);
				*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
			}
		}
		break;
	case 32:
		for (int j = y; j < y + h; j++) {
			for (int i = x; i < x + w; i++) {
				multiboot_uint32_t *pixel = fb + j * pitch + i * (bpp / 8);
				*pixel = color;
			}
		}
		break;
	}
}

void kernel_main() {

	/* Clear the screen. */
	cls();

	vbe_mode_info_t *vmi = mbi->vbe_mode_info;

	if (CHECK_FLAG(mbi->flags, 12)) {
		multiboot_uint32_t fb = vmi->physbase;
		multiboot_uint16_t pitch = vmi->pitch;
		multiboot_uint8_t bpp = vmi->bpp;
		fillrect(fb, 120, 60, 80, 20, bpp, pitch, 0x00ff0000);
	}

}

/* Clear the screen and initialize VIDEO, XPOS and YPOS. */
static void cls(void) {
	int i;

	video = (unsigned char *) VIDEO;

	for (i = 0; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;

	xpos = 0;
	ypos = 0;
}

/* Convert the integer D to a string and save the string in BUF. If
 BASE is equal to ’d’, interpret that D is decimal, and if BASE is
 equal to ’x’, interpret that D is hexadecimal. */
static void itoa(char *buf, int base, int d) {
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put ‘-’ in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	} else if (base == 'x')
		divisor = 16;

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

/* Put the character C on the screen. */
static void putchar(int c) {
	if (c == '\n' || c == '\r') {
		newline: xpos = 0;
		ypos++;
		if (ypos >= LINES)
			ypos = 0;
		return;
	}

	*(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
	*(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

	xpos++;
	if (xpos >= COLUMNS)
		goto newline;
}

/* Format a string and print it on the screen, just like the libc
 function printf. */
void printf(const char *format, ...) {
	char **arg = (char **) &format;
	int c;
	char buf[20];

	arg++;

	while ((c = *format++) != 0) {
		if (c != '%')
			putchar(c);
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
				itoa(buf, c, *((int *) arg++));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";

				string: for (p2 = p; *p2; p2++)
					;
				for (; p2 < p + pad; p2++)
					putchar(pad0 ? '0' : ' ');
				while (*p)
					putchar(*p++);
				break;

			default:
				putchar(*((int *) arg++));
				break;
			}
		}
	}
}
