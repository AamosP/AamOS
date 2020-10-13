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
#include <sys/types.h>
#include <aamOS/kernel.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

uint32_t detect_memory() {
	uint16_t total;
	uint8_t lowmem, highmem;

	outb(0x70, 0x30);
	lowmem = inb(0x71);
	outb(0x70, 0x31);
	highmem = inb(0x71);

	total = lowmem | highmem << 8;
	return (total) << 16;
}
