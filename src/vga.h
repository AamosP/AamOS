#ifndef VGA_H
#define VGA_H

#include <multiboot2.h>
#include <utils.h>

void VGA_init(struct multiboot_tag_framebuffer *tag);
void VGA_putpixel(uint32_t x, uint32_t y, uint32_t color);
void VGA_drawrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void VGA_drawchar(uint32_t x, uint32_t y, uint32_t c, uint32_t fg_color, uint32_t bg_color);
void VGA_print(uint32_t x, uint32_t y, uint8_t* s, uint32_t fg_color, uint32_t bg_color);

#endif
