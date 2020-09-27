#include <aamOS/kernel.h>

uint16_t *buf = (uint16_t*) 0xb8000;
int row = 0;
int col = 0;
uint16_t colour = 0x0000;

void set_fg(uint8_t fg) {
	colour = fg << 8 | colour;
}

void set_bg(uint8_t bg) {
	colour = bg << 12 | colour;
}

void write_char(const char c) {
	if (c == '\n') {
		row++;
		col = 0;
	} else {
		*(buf + col + row * 80) = colour | c;
		col++;
	}
}

void write_string(const char *s) {
	const char *f = s;
	while (*f != NULL) {
		write_char(*f);
		f++;
	}
}
