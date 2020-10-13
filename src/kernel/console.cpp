/*******************************************************************************
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2020 Aamos Pernu
 * 
 * AamOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AamOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this aamOS.  If not, see <https://www.gnu.org/licenses/>.
 ******************************************************************************/
#include <aamOS/kernel.h>
#include <console.h>
#include <asm/io.h>

uint16_t *buf = (uint16_t*) 0xb8000;
int row = 0;
int col = 0;
uint16_t colour = 0x0000;

void enable_cursor(uint8_t start, uint8_t end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

void disable_cursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor() {
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) ((row * 80 + col) & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) (((row * 80 + col) >> 8) & 0xFF));
}

void set_fg(uint8_t fg) {
	colour = fg << 8 | colour;
}

void set_bg(uint8_t bg) {
	colour = bg << 12 | colour;
}

void console_init(uint8_t bg, uint8_t fg) {
	set_bg(bg);
	set_fg(fg);
}

void write_char(const char c) {
	if (c == '\n' || c == '\r') {
		row++;
		col = 0;
	} else if(c == '\b') {
		col--;
		*(buf + col + row * 80) = colour | 0;
	} else {
		*(buf + col + row * 80) = colour | c;
		col++;
	}
	update_cursor();
}

void write_string(const char *s) {
	const char *f = s;
	while (*f != NULL) {
		write_char(*f);
		f++;
	}
}
