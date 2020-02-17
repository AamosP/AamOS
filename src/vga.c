#include <vga.h>
#include <multiboot.h>
#include <kernel.h>
#include <font.h>
#include <stddef.h>

vbe_mode_info_t *vmi;
vga_uint32_t LFB_addr;
vga_uint8_t bpp;
vga_uint16_t pitch;
vga_uint16_t Xres;
vga_uint16_t Yres;

void VGA_clear() {
	for (int i = 0; i < Xres; i++) {
		for (int j = 0; j < Yres; j++) {
			vga_uint32_t *pixel = LFB_addr + j * pitch + i * (bpp / 8);
			*pixel = 0;
		}
	}
}

void VGA_init(multiboot_info_t *mbi) {
	vmi = mbi->vbe_mode_info;
	LFB_addr = vmi->physbase;
	bpp = vmi->bpp;
	pitch = vmi->pitch;
	Xres = vmi->Xres;
	Yres = vmi->Yres;
	VGA_clear();
}

void VGA_putpixel(unsigned int x, unsigned int y, unsigned int color) {
	if (x <= Xres && y <= Yres) {
		vga_uint32_t *pixel = LFB_addr + y * pitch + x * (bpp / 8);
		if (bpp == 24) {
			*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
		} else
			*pixel = color;
	}
}

void VGA_fillrect(unsigned int x, unsigned int y, unsigned int w,
		unsigned int h, unsigned int color) {
	for (int i = x; i < w + x; i++) {
		for (int j = y; j < h + y; j++) {
			vga_uint32_t *pixel = LFB_addr + j * pitch + i * (bpp / 8);
			if (bpp == 24) {
				*pixel = (color & 0xffffff) | (*pixel & 0xff000000);
			} else
				*pixel = color;
		}
	}
}

void VGA_drawchar(unsigned int x, unsigned int y, vga_uint8_t c,
		unsigned int bg_color, unsigned int fg_color) {
	int l = 0;
	int h = 0;
	vga_uint8_t *char_data = &font_data[c * 8];
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

void VGA_writestring(unsigned int x, unsigned int y, vga_uint8_t *c,
		unsigned int bg_color, unsigned int fg_color) {
	int i = 0;
	while (c[i] != NULL) {
		VGA_drawchar(i * 8 + x, y, c[i], bg_color, fg_color);
		i++;
	}
}

void VGA_scroll(unsigned int pixels, char d) {
	vga_uint32_t *pixel;
	vga_uint32_t *pixel2;
	if (d == 'd') {
		for (int i = 0; i < Yres; i++) {
			for (int j = 0; j < Xres; j++) {
				pixel = LFB_addr + i * pitch + (j * bpp / 8);
				pixel2 = LFB_addr + (i + pixels) * pitch + (j * bpp / 8);
				*pixel = *pixel2;
			}
		}
	} else if (d == 'u') {
		for (int i = Yres; i > 0; i--) {
			for (int j = 0; j < Xres; j++) {
				pixel = LFB_addr + i * pitch + (j * bpp / 8);
				pixel2 = LFB_addr + (i - pixels) * pitch + (j * bpp / 8);
				*pixel = *pixel2;
			}
		}
	}
}
