/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>
#include <sys/types.h>
#include <multiboot.h>
#include <memory.h>

//static vbe_mode_info_t *tagfb;
static uint8_t *fb;
static uint32_t fbtype;
static uint32_t Xres;
static uint32_t Yres;
static uint32_t pitch;
static uint8_t bpp;

void VGA_init(multiboot_info_t *mbi) {
	//tagfb = tag;
//	char *s;
//	itoa(s, 'x', fb);
//	write_serial_str(s);
//	write_serial('\n');
	fbtype = mbi->framebuffer_type;
	Xres = mbi->framebuffer_width;
	Yres = mbi->framebuffer_height;
	pitch = mbi->framebuffer_pitch;
	bpp = mbi->framebuffer_bpp;
	fb = (void*) (unsigned long) mbi->framebuffer_addr;
	VGA_clear();
	//for(int i = 0; i < (pitch * Yres + (bpp / 8) * Xres); i++)tfb[i] = fb[i];
}

void VGA_putpixel(uint32_t x, uint32_t y, uint32_t color) {
	switch (bpp) {
	case 8: {
		uint8_t *pixel = fb + pitch * y + (bpp / 8) * x;
		*pixel = (uint8_t) color;
	}
		break;
	case 15:
	case 16: {
		uint16_t *pixel = (uint16_t*) (fb + pitch * y + (bpp / 8) * x);
		*pixel = (uint16_t) color;
	}
		break;
	case 24: {
		uint32_t *pixel = (uint32_t*) (fb + pitch * y + (bpp / 8) * x);
		*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
	}
		break;
	case 32: {
		uint32_t *pixel = (uint32_t*) (fb + pitch * y + (bpp / 8) * x);
		*pixel = color;
	}
		break;
	default: {
		uint32_t *pixel = (uint32_t*) (fb + pitch * y + (bpp / 8) * x);
		*pixel = color;
	}
		break;
	}
}

void VGA_drawrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height,
		uint32_t color) {
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			VGA_putpixel(i + x, j + y, color);
		}
	}
}

void VGA_drawchar(uint32_t x, uint32_t y, uint32_t c, uint32_t fg_color,
		uint32_t bg_color) {
	//uint8_t *data = &font_data[c * 8];
	uint32_t *pb = (uint32_t*) (fb + pitch * y + x * (bpp / 8));
	uint32_t b = pitch / (bpp / 8);
	uint8_t *data = get_font_data(c);
	for (unsigned int j = 0; j < 8; j++) {
		for (unsigned int i = 0; i < 8; i++) {
			if ((1 & (data[j] >> i))) {
				pb[i] = fg_color;
			} else {
				pb[i] = bg_color;
			}
		}
		pb += b;
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
}

uint32_t VGA_getpixel(uint32_t x, uint32_t y) {
	uint32_t *pixel = (uint32_t*) (fb + pitch * y + (bpp / 8) * x);
	return *pixel;
}

void VGA_scroll(char d, int p) {
	if (d == 'u') {
		uint32_t b = pitch / (bpp / 8);
		uint32_t bb = b * p;
		uint32_t *pb = (uint32_t*) fb;
		for (uint32_t i = 0; i < Yres; i++) {
			for (uint32_t j = 0; j < Xres; j++) {
				*(pb + j) = *(pb + j + bb);
			}
			pb += b;
		}
	}
}

void VGA_clear() {
	VGA_drawrect(0, 0, Xres, Yres, 0);
}
