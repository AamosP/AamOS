#include <aamOS/kernel.h>
#include <multiboot2.h>
#include <sys/types.h>
#include <printf.h>
#include <asm/system.h>
#include <asm/io.h>

extern void loadGdt(void);
extern void idt_init(void);
struct multiboot_tag* get_tag(uint32_t tag_type, unsigned long addr);
void kernel_main(unsigned long magic, unsigned long addr);

void kernel_main(unsigned long magic, unsigned long addr) {
	init_serial(COM1);
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		write_serial_str("Invalid Magic Number: 0x");
		char *s;
		itoa(s, 'x', magic);
		write_serial_str(s);
		write_serial_str("\nHalting System");
		__asm__("hlt");
		for (;;)
			;
	}
	struct multiboot_tag *tag;
	tag = get_tag(MULTIBOOT_TAG_TYPE_FRAMEBUFFER, addr);
	VGA_init(tag);
	console_init(tag, WHITE, BLACK);
	loadGdt();
	idt_init();
//	outb(0x21,0xfe);
//	outb(0xa1,0xff);
	sti();
//	write_serial('a');
	//console_print("Welcome To aamOS! \nUmm... so... there's not much here really. \nI've implemented interrupts and that's about it. \nNext up would probably be user mode... I dunno :D");
	//VGA_drawrect(20, 20, 20, 20, RED);
	//VGA_drawrect(20, 748, 20, 20, BLUE);
	printf("%c", 0xa5);
	//console_print("Hi!\n:DD");
}

struct multiboot_tag* get_tag(uint32_t tag_type, unsigned long addr) {
	struct multiboot_tag *tag;
//	tag = (struct multiboot_tag*) (addr + 8);
//	while (tag->type != tag_type) {
//		tag = (struct multiboot_tag*) ((uint8_t*) tag
//				+ ((tag->size + 7) & (unsigned) ~7));
//		if (tag->type == tag_type)
//			return tag;
//	}
//	return tag;
	unsigned size = *(unsigned*) addr;
	for (tag = (struct multiboot_tag*) (addr + 8);
			tag->type != MULTIBOOT_TAG_TYPE_END;
			tag = (struct multiboot_tag*) ((multiboot_uint8_t*) tag
					+ ((tag->size + 7) & ~7))) {
		if (tag->type == tag_type) {
			break;
		}
	}
	return tag;
}
