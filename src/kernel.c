#include <system.h>

extern void loadGdt(void);
extern void idt_init(void);
void kernel_main(unsigned long magic, unsigned long addr);

void kernel_main(unsigned long magic, unsigned long addr) {

	struct multiboot_tag *tag;
	tag = get_tag(MULTIBOOT_TAG_TYPE_FRAMEBUFFER, addr);
//
//	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
//		printf("Invalid Magic Number: 0x%x", magic);
//		return;
//	}
//
//	if (addr & 7) {
//		return;
//	}
	init_serial(COM1);
	loadGdt();
	idt_init();
//	isr_in();
//	irq_in();
//	outb(0x21,0xfd);
//	outb(0xa1,0xff);
	sti();
	VGA_init((struct multiboot_tag_framebuffer*) tag);
	console_init(tag, WHITE, BLACK);
//	kb_in();

//	char* s;
//	kb_in();
//	while(1) {
//		itoa(s, 'd', scancode);
//		write_serial_str(s);
//	}

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
