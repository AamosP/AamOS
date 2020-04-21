#include <system.h>

static uint32_t cols;
static uint32_t rows;

static uint32_t col;
static uint32_t row;

static uint8_t *data;

uint32_t fg_col;
uint32_t bg_col;

void console_init(struct multiboot_tag_framebuffer *tag, uint32_t fg,
		uint32_t bg) {
	VGA_init(tag);
	cols = tag->common.framebuffer_width / 8;
	rows = tag->common.framebuffer_height / 8;
	col = 0;
	row = 0;
	fg_col = fg;
	bg_col = bg;
	console_clear();
}

void console_clear() {
	for (int i = 0; i < (cols); i++) {
		for (int j = 0; j < (rows); j++) {
			VGA_drawrect(i * 8, j * 8, 8, 8, bg_col);
		}
	}
	col = 0;
	row = 0;
}

void console_putchar(char c) {
	if (col >= cols) {
		col = 0;
		row++;
	}
	if (row >= rows) {
		console_clear();
		row = 0;
		col = 0;
	}
	if (c == '\n' | c == '\r') {
		row++;
		if (row >= rows) {
			console_clear();
			row = 0;
		}
		col = 0;
	} else {
		VGA_drawchar(8 * col, 8 * row, c, fg_col, bg_col);
		col++;
	}
}

void console_print(char *s) {
	int i = 0;
	while (s[i]) {
		console_putchar(s[i]);
		i++;
	}
}
