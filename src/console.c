#include <console.h>
#include <multiboot2.h>
#include <utils.h>
#include <font.h>

static unsigned int cols;
static unsigned int rows;

static unsigned int col;
static unsigned int row;

static unsigned char *data;

static uint32_t fg_col;
static uint32_t bg_col;

void console_init(struct multiboot_tag_framebuffer *tag, uint32_t fg, uint32_t bg) {
	cols = tag->common.framebuffer_width / 8;
	rows = tag->common.framebuffer_height / 8;
	col = 0;
	row = 0;
	console_clear();
	console_putchar('H');
	fg_col = fg;
	bg_col = bg;
}

void console_clear() {
	for (int i = 0; i < (cols * rows); i++) {
		data[i] = 0;
	}
	col = 0;
	row = 0;
}

void console_putchar(char c) {
	if (row >= rows) {
		console_clear();
		row = 0;
		col = 0;
	}
	if (col >= cols) {
		col = 0;
		row++;
	}
	if(c != '\n')
		data[cols * row + col] = c;
	else {
		row++;
		if(row <= rows) {
			row = 0;
		}
		col=0;
	}
}

//void console_print(char *s) {
//	char *d = data[cols * row + col];
//	*d = s;
//}

void console_main() {
	data[cols * row + col] = 0x2503;
	for(int i = 0; i < cols; i++) {
		for(int j = 0; j < rows; j++) {
			VGA_drawchar(i*8, j*8, data[cols * j + i], fg_col, bg_col);
		}
	}
}
