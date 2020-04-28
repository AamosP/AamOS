/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>

static uint32_t cols;
static uint32_t rows;

static uint32_t index = 0;
static uint32_t row = 0;

static uint32_t fg_col;
static uint32_t bg_col;

static uint8_t *c_data;

uint64_t console_getcolor(uint32_t fg, uint32_t bg) {
	fg = fg_col;
	bg = bg_col;
	uint64_t c = (((uint64_t) fg) << 32) & (bg & 0x00000000ffffffff);
	return (c);
}

void console_setcolor(uint32_t fg, uint32_t bg) {
	fg_col = fg;
	bg_col = bg;
}

void console_init(multiboot_info_t *mbi, uint32_t fg, uint32_t bg) {
	VGA_init(mbi);
	cols = mbi->framebuffer_width / 8;
	rows = mbi->framebuffer_height / 8;
	index = 0;
	fg_col = fg;
	bg_col = bg;
}

void console_scroll() {
	VGA_scroll('u', 8);
	for (uint32_t i = 0; i < cols; i++) {
		c_data[i] = 0;
	}
	index = 0;
}

void console_putchar(char c) {
	if (index >= cols - 1) {
		VGA_drawchar(8 * index, 8 * row, 0, fg_col, bg_col);
		if (row < rows - 1) {
			row++;
		} else {
			console_scroll();
		}
		index = 0;
	}
	if ((c == '\n') | (c == '\r')) {
		VGA_drawchar(8 * index, 8 * row, 0, fg_col, bg_col);
		if (row < rows - 1) {
			row++;
		} else {
			console_scroll();
		}
		index = 0;
	} else if (c == 127) {
		if (index > 0) {
			VGA_drawchar(8 * index, 8 * row, 0, fg_col, bg_col);
			index--;
			c_data[index] = 0;
			VGA_drawchar(8 * index, 8 * row, 0, fg_col, bg_col);
		}
	} else if (c == '\t') {
		VGA_drawchar(8 * index, 8 * row, 0, fg_col, bg_col);
		c_data[index] = '\t';
		index += 4;
	} else {
		VGA_drawchar(8 * index, 8 * row, (uint32_t) c, fg_col, bg_col);
		c_data[index] = c;
		index++;
	}
}

void console_print(char *s) {
	int i = 0;
	while (s[i]) {
		console_putchar(s[i]);
		i++;
	}
	return;
}
