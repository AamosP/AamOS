#include <vga.h>
#include <multiboot.h>
#include <kernel.h>
#include <font.h>
#include <stddef.h>
#include <utils.h>

vbe_mode_info_t *vmi;
uint32_t LFB_addr;
uint8_t bpp;
uint16_t pitch;
uint16_t Xres;
uint16_t Yres;

void VGA_clear() {
	for (unsigned int i = 0; i < Xres; i++) {
		for (unsigned int j = 0; j < Yres; j++) {
			uint32_t *pixel = (uint32_t*)(LFB_addr + j * pitch + i * (bpp / 8));
			*pixel = 0;
		}
	}
}

void VGA_init(multiboot_info_t *mbi) {
	vmi = (vbe_mode_info_t*)mbi->vbe_mode_info;
	LFB_addr = vmi->physbase;
	bpp = vmi->bpp;
	pitch = vmi->pitch;
	Xres = vmi->Xres;
	Yres = vmi->Yres;
	VGA_clear();
}

void VGA_putpixel(unsigned int x, unsigned int y, unsigned int color) {
	if (x <= Xres && y <= Yres) {
		uint32_t *pixel = (uint32_t*)(LFB_addr + y * pitch + x * (bpp / 8));
		if (bpp == 24) {
			*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
		} else
			*pixel = color;
	}
}

void VGA_fillrect(unsigned int x, unsigned int y, unsigned int w,
		unsigned int h, unsigned int color) {
	for (unsigned int i = x; i < w + x; i++) {
		for (unsigned int j = y; j < h + y; j++) {
			uint32_t *pixel = (uint32_t*)(LFB_addr + j * pitch + i * (bpp / 8));
			if (bpp == 24
					&& *pixel != ((color & 0xffffff) | (*pixel & 0xff000000))) {
				*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
			} else if (*pixel != color)
				*pixel = color;
		}
	}
}

void VGA_drawchar(unsigned int x, unsigned int y, uint8_t c,
		unsigned int bg_color, unsigned int fg_color) {
	unsigned int l = 0;
	unsigned int h = 0;
	uint8_t *char_data = &font_data[c * 8];
	for (int i = 0; i < 8; i++) {
		l = 0;
		for (int j = 8; j > 0; j--) {
			l++;
			if ((char_data[i] & (1 << (8 - j)))) {
				VGA_putpixel(x + l, y + h, fg_color);
			} else
				VGA_putpixel(x + l, y + h, bg_color);
		}
		h++;
	}
}

void VGA_writestring(unsigned int x, unsigned int y, uint8_t *c,
		unsigned int bg_color, unsigned int fg_color) {
	unsigned int i = 0;
	while (c[i]) {
		VGA_drawchar(i * 8 + x, y, c[i], bg_color, fg_color);
		i++;
	}
}
