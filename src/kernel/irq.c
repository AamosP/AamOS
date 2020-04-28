#include <aamOS/kernel.h>
#include <asm/io.h>

static void (*irq_handlers[16])(
		registers_t*) = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void irq_handler(registers_t regs) {
	int in = regs.int_no - 32;
	if (in >= 8) {
		outb(0xa0, 0x20);
	}
	outb(0x20, 0x20);

	void (*handler)(registers_t*) = irq_handlers[in];
	if (handler) {
		handler(&regs);
	}
}

void register_irq_handler(int n, void (*h)(registers_t*)) {
	irq_handlers[n] = h;
}
