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
#ifndef _ISR_H
#define _ISR_H

#include <sys/types.h>

typedef struct registers
{
	uint32_t ds;					/* Data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 	/* Pushed by pusha. */
	uint32_t int_no, err_code;			/* Interrupt number and error code (if applicable) */
	uint32_t eip, cs, eflags, useresp, ss;		/* Pushed by the processor automatically. */
} registers_t;
typedef void (*isr_t)(registers_t);

struct IDT_entry {
	unsigned short int offset_lo;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_hi;
};

extern "C" void idt_init(void);

#endif
