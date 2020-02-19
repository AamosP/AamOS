#include <multiboot.h>
#include <stdint.h>
#include <kernel.h>
#include <vga.h>
#include <utils.h>
#include <font.h>
#include <keyboard.h>
#include <stddef.h>

/* Macros. */

/* Check if the bit BIT in FLAGS is set. */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

multiboot_info_t *mbi;

void kernel_main() {

	if (CHECK_FLAG(mbi->flags, 11)) {
		VGA_init(mbi);
		load_font_data();
		while (1) {
			init_kb();
			read_kb();
			unsigned char* s;
			for (int i = 0; i < 5; i++) {
				itoa(s, 'x', kb_data[i]);
				int l = 0;
				while (s[l] != NULL) {
					l++;
				}
				if (l < 2) {
					VGA_writestring(0, i*8, "0", 0, 0x00ffffff);
					VGA_writestring(8, i*8, s, 0, 0x00ffffff);
				} else VGA_writestring(0, i*8, s, 0, 0x00ffffff);
			}
		}
	}
}
