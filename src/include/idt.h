/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
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
