#include <multiboot.h>
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

void kernel_main(void);

void kernel_main() {
	if (CHECK_FLAG(mbi->flags, 11)) {
		VGA_init(mbi);
		init_kb();
		while (1) {
			read_kb();
			char* s = (char*)"";
			itoa(s, 'x', kb_data);
			int l = 0;
			while (s[l]) {
				l++;
			}
			if (l < 2) {
				VGA_writestring(8, 0, (uint8_t*)s, 0, 0x00ffffff);
				VGA_writestring(0, 0, (uint8_t*)"0", 0, 0x00ffffff);
			}
			VGA_writestring(0, 0, (uint8_t*)s, 0, 0x00ffffff);
		}
	}
}
