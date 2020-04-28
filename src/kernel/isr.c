#include <aamOS/kernel.h>

static void (*isr_handlers[32])(
		registers_t*) = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void isr_handler(registers_t *regs) {
	int in = regs->int_no;

	void (*handler)(registers_t*) = isr_handlers[in];
	if (handler) {
		handler(regs);
	}
}

void register_isr_handler(int n, void (*h)(registers_t*)) {
	isr_handlers[n] = h;
}

void DE(registers_t *regs) {
	write_serial_str("#DE\n");
}

void DB(registers_t *regs) {
	write_serial_str("#DB\n");
}

void NMI(registers_t *regs) {
	write_serial_str("Non-maskable Interrupt\n");
}

void BP(registers_t *regs) {
	write_serial_str("#BP\n");
}

void OF(registers_t *regs) {
	write_serial_str("#OF\n");
}

void BR(registers_t *regs) {
	write_serial_str("#BR\n");
}

void UD(registers_t *regs) {
	write_serial_str("#UD\n");
}

void NM(registers_t *regs) {
	write_serial_str("#NM\n");
}

void DF(registers_t *regs) {
	write_serial_str("#DF(");
	char *s;
	itoa(s, 'd', regs->err_code);
	write_serial_str(s);
	write_serial_str(")\n");
}

void CSO(registers_t *regs) {
	write_serial_str("Coprocessor Segment Overrun");
}

void TS(registers_t *regs) {
	write_serial_str("#TS(");
	char *s;
	itoa(s, 'd', regs->err_code);
	write_serial_str(s);
	write_serial_str(")\n");
}

void NP(registers_t *regs) {
	write_serial_str("#NP(");
	char *s;
	itoa(s, 'd', regs->err_code);
	write_serial_str(s);
	write_serial_str(")\n");
}

void SS(registers_t *regs) {
	write_serial_str("#SS(");
	char *s;
	itoa(s, 'd', regs->err_code);
	write_serial_str(s);
	write_serial_str(")\n");
}

void GP(registers_t *regs) {
	write_serial_str("#GP(");
	char s;
	itoa(&s, 'd', regs->err_code);
	write_serial_str(&s);
	write_serial_str(")\n");
}

void PF(registers_t *regs) {
	write_serial_str("#PF(");
	char *s;
	itoa(s, 'd', regs->err_code);
	write_serial_str(s);
	write_serial_str(")\n");
}

/* ISR15 is reserved by intel */

void MF(registers_t *regs) {
	write_serial_str("#MF\n");
}

void AC(registers_t *regs) {
	write_serial_str("#AC\n");
}

void MC(registers_t *regs) {
	write_serial_str("#MC\n");
}

void XM(registers_t *regs) {
	write_serial_str("#XM\n");
}

void VE(registers_t *regs) {
	write_serial_str("#VE\n");
}

/* ISRs 21-29 are reserved by intel */

void SX(registers_t *regs) {
	write_serial_str("#SX\n");
}

/* ISR 31 is reserved by intel */

void init_isrs() {
	register_isr_handler(0, DE);
	register_isr_handler(1, DB);
	register_isr_handler(2, NMI);
	register_isr_handler(3, BP);
	register_isr_handler(4, OF);
	register_isr_handler(5, BR);
	register_isr_handler(6, UD);
	register_isr_handler(7, NM);
	register_isr_handler(8, DF);
	register_isr_handler(9, CSO);
	register_isr_handler(10, TS);
	register_isr_handler(11, NP);
	register_isr_handler(12, SS);
	register_isr_handler(13, GP);
	register_isr_handler(14, PF);
	register_isr_handler(16, MF);
	register_isr_handler(17, AC);
	register_isr_handler(18, MC);
	register_isr_handler(19, XM);
	register_isr_handler(20, VE);
	register_isr_handler(30, SX);
}
