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

void timer() {
  //write_serial('1');
}
