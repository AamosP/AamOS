//#include <aamOS/kernel.h>
#include <asm/io.h>
#include <idt.h>
#include <stdio.h>

static void (*irq_handlers[16])(
		registers_t*) = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

extern "C" void irq_handler(registers_t regs) {
	//__asm__ __volatile__ ("xchg %bx,%bx");
	//printf(
	//			"ds: %x\n edi: %x   esi: %x   ebp: %x   esp: %x\nebx: %x   edx: %x   ecx: %x   eax: %x\nint_no: %x   err_code: %x\n eip: %x   cs: %x   eflags: %x   useresp: %x   ss: %x\n\n",
	//			regs.ds, regs.edi, regs.esi, regs.ebp, regs.esp, regs.ebx,
	//			regs.edx, regs.ecx, regs.eax, regs.int_no, regs.err_code,
	//			regs.eip, regs.cs, regs.eflags, regs.useresp, regs.ss);

	int in = regs.int_no - 32;

	outb(0x20, 0x20);
	if (in >= 8) {
		outb(0xa0, 0x20);
	}

	void (*handler)(registers_t*) = irq_handlers[in];
	if (handler) {
		handler(&regs);
	}
}

void register_irq_handler(int n, void (*h)(registers_t*)) {
	irq_handlers[n] = h;
}
