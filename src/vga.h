#ifndef VGA_H
#define VGA_H

#include <kernel.h>

typedef unsigned char vga_uint8_t;
typedef unsigned short vga_uint16_t;
typedef unsigned int vga_uint32_t;
typedef unsigned long long vga_uint64_t;

extern void VGA_fillrect(unsigned int x, unsigned int y, unsigned int w,
		unsigned int h, unsigned int color);
extern void VGA_putpixel(unsigned int x, unsigned int y, unsigned int color);
extern void VGA_clear();
extern void VGA_drawchar(unsigned int x, unsigned int y, vga_uint8_t c,
		unsigned int bg_color, unsigned int fg_color);
extern void VGA_writestring(unsigned int x, unsigned int y, vga_uint8_t *c,
		unsigned int bg_color, unsigned int fg_color);
extern void VGA_scroll(unsigned int pixels, char d);

extern vga_uint16_t Xres;
extern vga_uint16_t Yres;

#endif
