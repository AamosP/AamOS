#ifndef VGA_H
#define VGA_H

#include <utils.h>
#include <kernel.h>

void VGA_init(multiboot_info_t* mbi);
void VGA_fillrect(unsigned int x, unsigned int y, unsigned int w,
		unsigned int h, unsigned int color);
void VGA_putpixel(unsigned int x, unsigned int y, unsigned int color);
void VGA_clear(void);
void VGA_drawchar(unsigned int x, unsigned int y, uint8_t c,
		unsigned int bg_color, unsigned int fg_color);
void VGA_writestring(unsigned int x, unsigned int y, uint8_t *c,
		unsigned int bg_color, unsigned int fg_color);
void VGA_scroll(unsigned int pixels, char d);

#endif
