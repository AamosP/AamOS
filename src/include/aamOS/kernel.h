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
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/types.h>
#include <idt.h>
#include <stdarg.h>
#include <asm/io.h>
#include <asm/system.h>
#include <timer.h>
#include <serial.h>

void irq0_handler(void);
void irq1_handler(void);
void irq2_handler(void);
void irq3_handler(void);
void irq4_handler(void);
void irq5_handler(void);
void irq6_handler(void);
void irq7_handler(void);
void irq8_handler(void);
void irq9_handler(void);
void irq10_handler(void);
void irq11_handler(void);
void irq12_handler(void);
void irq13_handler(void);
void irq14_handler(void);
void irq15_handler(void);

void itoa(char *buf, int base, int d);
void dump_struct(void* structure, size_t bytes);
int oct2bin(unsigned char *str, int size);
void panic(const char *s);

char get_queue(void);
void kb_init(void);
void kb_handler(registers_t *regs);

void idt_set_gate (uint8_t num, uint32_t offset, uint16_t sel, uint8_t flags);

void register_isr_handler(int n, void (*h)(registers_t*));
void init_isrs(void);

void register_irq_handler(int n, void (*h)(registers_t*));
void init_irqs(void);

#endif
