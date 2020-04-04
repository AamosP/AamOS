#include <vga.h>
#include <multiboot2.h>
#include <utils.h>
#include <font.h>
#include <stddef.h>

static struct multiboot_tag_framebuffer *tagfb;
static uint8_t *fb;
static uint32_t fbtype;
static uint32_t Xres;
static uint32_t Yres;
static uint32_t pitch;
static uint8_t bpp;

void VGA_init(struct multiboot_tag_framebuffer *tag) {
	tagfb = tag;
	fb = (void*) (unsigned long) tagfb->common.framebuffer_addr;
	fbtype = tagfb->common.framebuffer_type;
	Xres = tagfb->common.framebuffer_width;
	Yres = tagfb->common.framebuffer_height;
	pitch = tagfb->common.framebuffer_pitch;
	bpp = tagfb->common.framebuffer_bpp;
	return;
}

void VGA_putpixel(uint32_t x, uint32_t y, uint32_t color) {
	switch (bpp) {
	case 8: {
		uint8_t *pixel = fb + pitch * y + (bpp / 8) * x;
		*pixel = (uint8_t)color;
	}
		break;
	case 15:
	case 16: {
		uint16_t *pixel = (uint16_t*)((uint32_t)(fb) + pitch * y + 2 * x);
		*pixel = (uint16_t)color;
	}
		break;
	case 24: {
		uint32_t *pixel = (uint32_t*)((uint32_t)(fb) + pitch * y + 3 * x);
		*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
	}
		break;
	case 32: {
		uint32_t *pixel = (uint32_t*)((uint32_t)(fb) + pitch * y + 4 * x);
		*pixel = color;
	}
		break;
	}
	return;
}

void VGA_drawrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height,
		uint32_t color) {
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			VGA_putpixel(i + x, j + y, color);
		}
	}
	return;
}

void VGA_drawchar(uint32_t x, uint32_t y, uint32_t c, uint32_t fg_color,
		uint32_t bg_color) {
	//uint8_t *data = &font_data[c * 8];
	uint8_t *data = get_font_data(c);
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			if ((1 & (data[j] >> i))) {
				VGA_putpixel(i + x, j + y, fg_color);
			} else
				VGA_putpixel(i + x, j + y, bg_color);
		}
	}
	return;
}

void VGA_print(uint32_t x, uint32_t y, uint8_t *s, uint32_t fg_color,
		uint32_t bg_color) {
	unsigned int i = 0;
	while (s[i]) {
		VGA_drawchar(x + i * 8, y, s[i], fg_color, bg_color);
		i++;
	}
	return;
}
