#include <asm/io.h>
#include <asm/system.h>

void idt_init(void);

struct IDT_entry {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[256];

int isr0(void) {
	write_serial_str("Divide-by-zero Exception\n");
	iret();
}

int isr1(void) {
	write_serial_str("Debug Exception\n");
	iret();
}

int isr2(void) {
	write_serial_str("Non-maskable Interrupt Exception\n");
	iret();
}

int isr3(void) {
	write_serial_str("Breakpoint Exception\n");
	iret();
}

int isr4(void) {
	write_serial_str("Overflow Exception\n");
	iret();
}

int isr5(void) {
	write_serial_str("Bound Range Exceeded\n");
	iret();
}

int isr6(void) {
	write_serial_str("Invalid Opcode\n");
	iret();
}

int isr7(void) {
	write_serial_str("Device Not Available\n");
	iret();
}

int isr8(void) {
	write_serial_str("Double Fault\n");
	iret();
}

int isr9(void) {
	write_serial_str("Coprocessor Segment Overrun Exception\n");
	iret();
}

int isr10(void) {
	write_serial_str("Invalid TSS Exception\n");
	iret();
}

int isr11(void) {
	write_serial_str("Segment Not Present Exception\n");
	iret();
}

int isr12(void) {
	write_serial_str("Stack-Segment Fault\n");
	iret();
}

int isr13(void) {
	write_serial_str("General Protection Fault\n");
	iret();
}

int isr14(void) {
	write_serial_str("Page Fault\n");
	iret();
}

int isr16(void) {
	write_serial_str("x87 Floating-Point Exception\n");
	iret();
}

int isr17(void) {
	write_serial_str("Alignment Check Exception\n");
	iret();
}

int isr18(void) {
	write_serial_str("Machine Check Exception\n");
	iret();
}

int isr19(void) {
	write_serial_str("SIMD Floating-Point Exception\n");
	iret();
}

int isr20(void) {
	write_serial_str("Virtualization Exception\n");
	iret();
}

int isr30(void) {
	write_serial_str("Security Exception\n");
	iret();
}

int isr_reserved(void) {
	write_serial_str("Reserved Exception\n");
	iret();
}

void idt_init(void) {
	extern int loadIdt(unsigned long*);
	extern int irq0(void);
	extern int irq1(void);
	extern int irq2(void);
	extern int irq3(void);
	extern int irq4(void);
	extern int irq5(void);
	extern int irq6(void);
	extern int irq7(void);
	extern int irq8(void);
	extern int irq9(void);
	extern int irq10(void);
	extern int irq11(void);
	extern int irq12(void);
	extern int irq13(void);
	extern int irq14(void);
	extern int irq15(void);

	unsigned long irq0_address;
	unsigned long irq1_address;
	unsigned long irq2_address;
	unsigned long irq3_address;
	unsigned long irq4_address;
	unsigned long irq5_address;
	unsigned long irq6_address;
	unsigned long irq7_address;
	unsigned long irq8_address;
	unsigned long irq9_address;
	unsigned long irq10_address;
	unsigned long irq11_address;
	unsigned long irq12_address;
	unsigned long irq13_address;
	unsigned long irq14_address;
	unsigned long irq15_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	unsigned long isr0_address;
	unsigned long isr1_address;
	unsigned long isr2_address;
	unsigned long isr3_address;
	unsigned long isr4_address;
	unsigned long isr5_address;
	unsigned long isr6_address;
	unsigned long isr7_address;
	unsigned long isr8_address;
	unsigned long isr9_address;
	unsigned long isr10_address;
	unsigned long isr11_address;
	unsigned long isr12_address;
	unsigned long isr13_address;
	unsigned long isr14_address;
	unsigned long isr16_address;
	unsigned long isr17_address;
	unsigned long isr18_address;
	unsigned long isr19_address;
	unsigned long isr20_address;
	unsigned long isr_reserved_address;
	unsigned long isr30_address;

	isr0_address = (unsigned long) isr0;
	IDT[0].offset_lowerbits = isr0_address & 0xffff;
	IDT[0].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0].zero = 0;
	IDT[0].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[0].offset_higherbits = (isr0_address & 0xffff0000) >> 16;

	isr1_address = (unsigned long) isr1;
	IDT[1].offset_lowerbits = isr1_address & 0xffff;
	IDT[1].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[1].zero = 0;
	IDT[1].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[1].offset_higherbits = (isr1_address & 0xffff0000) >> 16;

	isr2_address = (unsigned long) isr2;
	IDT[2].offset_lowerbits = isr2_address & 0xffff;
	IDT[2].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[2].zero = 0;
	IDT[2].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[2].offset_higherbits = (isr2_address & 0xffff0000) >> 16;

	isr3_address = (unsigned long) isr3;
	IDT[3].offset_lowerbits = isr3_address & 0xffff;
	IDT[3].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[3].zero = 0;
	IDT[3].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[3].offset_higherbits = (isr3_address & 0xffff0000) >> 16;

	isr4_address = (unsigned long) isr4;
	IDT[4].offset_lowerbits = isr4_address & 0xffff;
	IDT[4].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[4].zero = 0;
	IDT[4].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[4].offset_higherbits = (isr4_address & 0xffff0000) >> 16;

	isr18_address = (unsigned long) isr5;
	IDT[5].offset_lowerbits = isr5_address & 0xffff;
	IDT[5].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[5].zero = 0;
	IDT[5].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[5].offset_higherbits = (isr5_address & 0xffff0000) >> 16;

	isr6_address = (unsigned long) isr6;
	IDT[6].offset_lowerbits = isr6_address & 0xffff;
	IDT[6].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[6].zero = 0;
	IDT[6].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[6].offset_higherbits = (isr6_address & 0xffff0000) >> 16;

	isr7_address = (unsigned long) isr7;
	IDT[7].offset_lowerbits = isr7_address & 0xffff;
	IDT[7].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[7].zero = 0;
	IDT[7].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[7].offset_higherbits = (isr7_address & 0xffff0000) >> 16;

	isr8_address = (unsigned long) isr8;
	IDT[8].offset_lowerbits = isr8_address & 0xffff;
	IDT[8].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[8].zero = 0;
	IDT[8].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[8].offset_higherbits = (isr8_address & 0xffff0000) >> 16;

	isr9_address = (unsigned long) isr9;
	IDT[9].offset_lowerbits = isr9_address & 0xffff;
	IDT[9].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[9].zero = 0;
	IDT[9].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[9].offset_higherbits = (isr9_address & 0xffff0000) >> 16;

	isr10_address = (unsigned long) isr10;
	IDT[10].offset_lowerbits = isr10_address & 0xffff;
	IDT[10].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[10].zero = 0;
	IDT[10].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[10].offset_higherbits = (isr10_address & 0xffff0000) >> 16;

	isr11_address = (unsigned long) isr11;
	IDT[11].offset_lowerbits = isr11_address & 0xffff;
	IDT[11].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[11].zero = 0;
	IDT[11].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[11].offset_higherbits = (isr11_address & 0xffff0000) >> 16;

	isr12_address = (unsigned long) isr12;
	IDT[12].offset_lowerbits = isr12_address & 0xffff;
	IDT[12].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[12].zero = 0;
	IDT[12].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[12].offset_higherbits = (isr12_address & 0xffff0000) >> 16;

	isr13_address = (unsigned long) isr13;
	IDT[13].offset_lowerbits = isr13_address & 0xffff;
	IDT[13].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[13].zero = 0;
	IDT[13].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[13].offset_higherbits = (isr13_address & 0xffff0000) >> 16;

	isr14_address = (unsigned long) isr14;
	IDT[14].offset_lowerbits = isr14_address & 0xffff;
	IDT[14].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[14].zero = 0;
	IDT[14].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[14].offset_higherbits = (isr14_address & 0xffff0000) >> 16;

	isr_reserved_address = (unsigned long) isr_reserved;
	IDT[15].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[15].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[15].zero = 0;
	IDT[15].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[15].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	isr16_address = (unsigned long) isr16;
	IDT[16].offset_lowerbits = isr16_address & 0xffff;
	IDT[16].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[16].zero = 0;
	IDT[16].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[16].offset_higherbits = (isr16_address & 0xffff0000) >> 16;

	isr17_address = (unsigned long) isr17;
	IDT[17].offset_lowerbits = isr17_address & 0xffff;
	IDT[17].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[17].zero = 0;
	IDT[17].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[17].offset_higherbits = (isr17_address & 0xffff0000) >> 16;

	isr18_address = (unsigned long) isr18;
	IDT[18].offset_lowerbits = isr18_address & 0xffff;
	IDT[18].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[18].zero = 0;
	IDT[18].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[18].offset_higherbits = (isr18_address & 0xffff0000) >> 16;

	isr19_address = (unsigned long) isr19;
	IDT[19].offset_lowerbits = isr19_address & 0xffff;
	IDT[19].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[19].zero = 0;
	IDT[19].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[19].offset_higherbits = (isr19_address & 0xffff0000) >> 16;

	isr20_address = (unsigned long) isr20;
	IDT[20].offset_lowerbits = isr20_address & 0xffff;
	IDT[20].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[20].zero = 0;
	IDT[20].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[20].offset_higherbits = (isr20_address & 0xffff0000) >> 16;

	IDT[21].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[21].zero = 0;
	IDT[21].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[21].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[22].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[22].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[22].zero = 0;
	IDT[22].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[22].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[23].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[23].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[23].zero = 0;
	IDT[23].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[23].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[24].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[24].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[24].zero = 0;
	IDT[24].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[24].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[25].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[25].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[25].zero = 0;
	IDT[25].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[25].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[26].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[26].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[26].zero = 0;
	IDT[26].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[26].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[27].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[27].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[27].zero = 0;
	IDT[27].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[27].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[28].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[28].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[28].zero = 0;
	IDT[28].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[28].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	IDT[29].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[29].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[29].zero = 0;
	IDT[29].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[29].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	isr30_address = (unsigned long) isr30;
	IDT[30].offset_lowerbits = isr30_address & 0xffff;
	IDT[30].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[30].zero = 0;
	IDT[30].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[30].offset_higherbits = (isr30_address & 0xffff0000) >> 16;

	IDT[31].offset_lowerbits = isr_reserved_address & 0xffff;
	IDT[31].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[31].zero = 0;
	IDT[31].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[31].offset_higherbits = (isr_reserved_address & 0xffff0000) >> 16;

	/* remapping the PIC */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 40);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	irq0_address = (unsigned long) irq0;
	IDT[32].offset_lowerbits = irq0_address & 0xffff;
	IDT[32].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[32].zero = 0;
	IDT[32].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[32].offset_higherbits = (irq0_address & 0xffff0000) >> 16;

	irq1_address = (unsigned long) irq1;
	IDT[33].offset_lowerbits = irq1_address & 0xffff;
	IDT[33].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[33].zero = 0;
	IDT[33].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[33].offset_higherbits = (irq1_address & 0xffff0000) >> 16;

	irq2_address = (unsigned long) irq2;
	IDT[34].offset_lowerbits = irq2_address & 0xffff;
	IDT[34].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[34].zero = 0;
	IDT[34].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[34].offset_higherbits = (irq2_address & 0xffff0000) >> 16;

	irq3_address = (unsigned long) irq3;
	IDT[35].offset_lowerbits = irq3_address & 0xffff;
	IDT[35].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[35].zero = 0;
	IDT[35].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[35].offset_higherbits = (irq3_address & 0xffff0000) >> 16;

	irq4_address = (unsigned long) irq4;
	IDT[36].offset_lowerbits = irq4_address & 0xffff;
	IDT[36].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[36].zero = 0;
	IDT[36].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[36].offset_higherbits = (irq4_address & 0xffff0000) >> 16;

	irq5_address = (unsigned long) irq5;
	IDT[37].offset_lowerbits = irq5_address & 0xffff;
	IDT[37].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[37].zero = 0;
	IDT[37].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[37].offset_higherbits = (irq5_address & 0xffff0000) >> 16;

	irq6_address = (unsigned long) irq6;
	IDT[38].offset_lowerbits = irq6_address & 0xffff;
	IDT[38].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[38].zero = 0;
	IDT[38].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[38].offset_higherbits = (irq6_address & 0xffff0000) >> 16;

	irq7_address = (unsigned long) irq7;
	IDT[39].offset_lowerbits = irq7_address & 0xffff;
	IDT[39].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[39].zero = 0;
	IDT[39].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[39].offset_higherbits = (irq7_address & 0xffff0000) >> 16;

	irq8_address = (unsigned long) irq8;
	IDT[40].offset_lowerbits = irq8_address & 0xffff;
	IDT[40].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[40].zero = 0;
	IDT[40].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[40].offset_higherbits = (irq8_address & 0xffff0000) >> 16;

	irq9_address = (unsigned long) irq9;
	IDT[41].offset_lowerbits = irq9_address & 0xffff;
	IDT[41].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[41].zero = 0;
	IDT[41].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[41].offset_higherbits = (irq9_address & 0xffff0000) >> 16;

	irq10_address = (unsigned long) irq10;
	IDT[42].offset_lowerbits = irq10_address & 0xffff;
	IDT[42].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[42].zero = 0;
	IDT[42].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[42].offset_higherbits = (irq10_address & 0xffff0000) >> 16;

	irq11_address = (unsigned long) irq11;
	IDT[43].offset_lowerbits = irq11_address & 0xffff;
	IDT[43].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[43].zero = 0;
	IDT[43].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[43].offset_higherbits = (irq11_address & 0xffff0000) >> 16;

	irq12_address = (unsigned long) irq12;
	IDT[44].offset_lowerbits = irq12_address & 0xffff;
	IDT[44].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[44].zero = 0;
	IDT[44].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[44].offset_higherbits = (irq12_address & 0xffff0000) >> 16;

	irq13_address = (unsigned long) irq13;
	IDT[45].offset_lowerbits = irq13_address & 0xffff;
	IDT[45].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[45].zero = 0;
	IDT[45].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[45].offset_higherbits = (irq13_address & 0xffff0000) >> 16;

	irq14_address = (unsigned long) irq14;
	IDT[46].offset_lowerbits = irq14_address & 0xffff;
	IDT[46].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[46].zero = 0;
	IDT[46].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[46].offset_higherbits = (irq14_address & 0xffff0000) >> 16;

	irq15_address = (unsigned long) irq15;
	IDT[47].offset_lowerbits = irq15_address & 0xffff;
	IDT[47].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[47].zero = 0;
	IDT[47].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[47].offset_higherbits = (irq15_address & 0xffff0000) >> 16;

	/* fill the IDT descriptor */
	idt_address = (unsigned long) IDT;
	idt_ptr[0] = (sizeof(struct IDT_entry) * 256)
			+ ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16;

	loadIdt(idt_ptr);

}
