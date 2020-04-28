/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>
#include <asm/io.h>

void set_timer_freq(int hz) {
	int d = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, d & 0xFF);
	outb(0x40, d >> 8);
}

void timer_init() {
	register_irq_handler(0, timer);
	set_timer_freq(100);
}

void timer(registers_t *regs) {
  //write_serial('1');
}
