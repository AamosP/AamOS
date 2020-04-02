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
			print("Hi!", 0, 0, 0x0000000000ffffff);
		}
	}
}
