/*******************************************************************************
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2020 Aamos Pernu
 * 
 * AamOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AamOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this aamOS.  If not, see <https://www.gnu.org/licenses/>.
 ******************************************************************************/
#include <aamOS/kernel.h>
#include <asm/io.h>
#include <stdio.h>

unsigned int i;

void set_timer_freq(uint32_t hz) {
	uint32_t d = 1193180 / hz;
	outb(0x43, 0x36);
	outb(0x40, d & 0xFF);
	outb(0x40, d >> 8);
}

void timer_init() {
	register_irq_handler(0, timer);
	set_timer_freq(100);
	i = 0;
}

void timer(registers_t *regs) {
	//write_serial('1');
	i++;
	//const char* s = "";
	//itoa((char*)s, 'x', regs->err_code);
	//write_serial_str(s);
}

void sleep(uint32_t d) {
	uint32_t n = i + d;
	while(i < n)asm("hlt");
}
