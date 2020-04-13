#include <multiboot2.h>
#include <kernel.h>
#include <vga.h>
#include <utils.h>
#include <font.h>
#include <keyboard.h>
#include <stddef.h>
#include <console.h>
#include <serial.h>
#include <int.h>

void kernel_main(unsigned long magic, unsigned long addr);
struct multiboot_tag* get_tag(uint32_t tag_type, unsigned long addr);

void kernel_main(unsigned long magic, unsigned long addr) {
	struct multiboot_tag *tag;

	tag = get_tag(MULTIBOOT_TAG_TYPE_FRAMEBUFFER, addr);
	VGA_init((struct multiboot_tag_framebuffer*) tag);

	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		VGA_print(0, 0, (uint8_t*) "Invalid magic number", 0x00ff0000, 0);
		return;
	}

	if (addr & 7) {
		return;
	}

	init_serial();
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
}

struct multiboot_tag* get_tag(uint32_t tag_type, unsigned long addr) {
	struct multiboot_tag *tag;
	tag = (struct multiboot_tag*) (addr + 8);
	while (tag->type != tag_type) {
		tag = (struct multiboot_tag*) ((uint8_t*) tag
				+ ((tag->size + 7) & (unsigned) ~7));
	}
	return tag;
}
