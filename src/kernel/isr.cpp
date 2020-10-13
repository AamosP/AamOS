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
#include <stdio.h>
#include <paging.h>

static void (*isr_handlers[32])(
		registers_t*) = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

extern "C" void isr_handler(registers_t regs) {
	//printf(
	//		"ds: %x\n edi: %x   esi: %x   ebp: %x   esp: %x\nebx: %x   edx: %x   ecx: %x   eax: %x\nint_no: %x   err_code: %x\n eip: %x   cs: %x   eflags: %x   useresp: %x   ss: %x\n\n",
	//		regs.ds, regs.edi, regs.esi, regs.ebp, regs.esp, regs.ebx,
	//		regs.edx, regs.ecx, regs.eax, regs.int_no, regs.err_code,
	//		regs.eip, regs.cs, regs.eflags, regs.useresp, regs.ss);

	int in = regs.int_no;

	void (*handler)(registers_t*) = isr_handlers[in];
	if (handler) {
		handler(&regs);
	}
}

void register_isr_handler(int n, void (*h)(registers_t*)) {
	isr_handlers[n] = h;
}

void DE(registers_t *regs) {
	printf("#DE\n");
	dump_struct(regs, sizeof(regs));
}

void DB(registers_t *regs) {
	printf("#DB\n");
	dump_struct(regs, sizeof(regs));
}

void NMI(registers_t *regs) {
	printf("Non-maskable Interrupt\n");
	dump_struct(regs, sizeof(regs));
}

void BP(registers_t *regs) {
	printf("#BP\n");
	dump_struct(regs, sizeof(regs));
}

void OF(registers_t *regs) {
	printf("#OF\n");
	dump_struct(regs, sizeof(regs));
}

void BR(registers_t *regs) {
	printf("#BR\n");
	dump_struct(regs, sizeof(regs));
}

void UD(registers_t *regs) {
	printf("#UD\n");
	dump_struct(regs, sizeof(regs));
}

void NM(registers_t *regs) {
	printf("#NM\n");
	dump_struct(regs, sizeof(regs));
}

void DF(registers_t *regs) {
	printf("#DF(%i)\n", regs->err_code);
	dump_struct(regs, sizeof(regs));
}

void CSO(registers_t *regs) {
	printf("Coprocessor Segment Overrun");
	dump_struct(regs, sizeof(regs));
}

void TS(registers_t *regs) {
	printf("#TS(%i)\n", regs->err_code);
	dump_struct(regs, sizeof(regs));
}

void NP(registers_t *regs) {
	printf("#NP(%i)\n", regs->err_code);
	dump_struct(regs, sizeof(regs));
}

void SS(registers_t *regs) {
	printf("#SS(%i)\n", regs->err_code);
	dump_struct(regs, sizeof(regs));
}

void GP(registers_t *regs) {
	printf("#GP(%i)\n", regs->err_code);
	dump_struct(regs, sizeof(regs));
}

//void PF(registers_t *regs) {
//	printf("#PF(%i)\n", regs->err_code);
//	dump_struct(regs, sizeof(regs));
//}

/* ISR15 is reserved by intel */

void MF(registers_t *regs) {
	printf("#MF\n");
	dump_struct(regs, sizeof(regs));
}

void AC(registers_t *regs) {
	printf("#AC\n");
	dump_struct(regs, sizeof(regs));
}

void MC(registers_t *regs) {
	printf("#MC\n");
	dump_struct(regs, sizeof(regs));
}

void XM(registers_t *regs) {
	printf("#XM\n");
	dump_struct(regs, sizeof(regs));
}

void VE(registers_t *regs) {
	printf("#VE\n");
	dump_struct(regs, sizeof(regs));
}

/* ISRs 21-29 are reserved by intel */

void SX(registers_t *regs) {
	printf("#SX\n");
	dump_struct(regs, sizeof(regs));
}

/* ISR 31 is reserved by intel */

void init_isrs() {
	//register_isr_handler(0, DE);
	//register_isr_handler(1, DB);
	//register_isr_handler(2, NMI);
	//register_isr_handler(3, BP);
	//register_isr_handler(4, OF);
	//register_isr_handler(5, BR);
	//register_isr_handler(6, UD);
	//register_isr_handler(7, NM);
	//register_isr_handler(8, DF);
	//register_isr_handler(9, CSO);
	//register_isr_handler(10, TS);
	//register_isr_handler(11, NP);
	//register_isr_handler(12, SS);
	register_isr_handler(13, GP);
	register_isr_handler(14, page_fault);
	//register_isr_handler(16, MF);
	//register_isr_handler(17, AC);
	//register_isr_handler(18, MC);
	//register_isr_handler(19, XM);
	//register_isr_handler(20, VE);
	//register_isr_handler(30, SX);
}
