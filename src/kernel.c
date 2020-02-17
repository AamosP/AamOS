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
uint64_t *gdt;

extern void storeIdt();

struct IDTDescr {
	uint16_t offset_1; // offset bits 0..15
	uint16_t selector; // a code segment selector in GDT or LDT
	uint8_t zero;      // unused, set to 0
	uint8_t type_attr; // type and attributes, see below
	uint16_t offset_2; // offset bits 16..31
};
struct IDTDescr *idt;

void kernel_main() {

	if (CHECK_FLAG(mbi->flags, 11)) {
		VGA_init(mbi);
		load_font_data();
		storeIdt();
		unsigned char *s;
		itoa(s, 'b', idt->offset_1);
		VGA_writestring(0, 0, s, 0, 0x00ffffff);
		itoa(s, 'b', idt->selector);
		VGA_writestring(0, 8, s, 0, 0x00ffffff);
		itoa(s, 'b', idt->zero);
		VGA_writestring(0, 16, s, 0, 0x00ffffff);
		itoa(s, 'b', idt->type_attr);
		VGA_writestring(0, 24, s, 0, 0x00ffffff);
		itoa(s, 'b', idt->offset_2);
		VGA_writestring(0, 32, s, 0, 0x00ffffff);
	}
}
