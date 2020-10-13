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
#include <idt.h>
#include <aamOS/kernel.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <console.h>
#include <memory.h>
#include <string.h>
#include <paging.h>

extern "C" void kmain() {
	init_serial(COM1);
	idt_init();
	sti();
	console_init(BLACK, WHITE);
	kb_init();
	init_isrs();
	timer_init();
	time_init();
	while (1) {
	}
}
