#ifndef SERIAL_H
#define SERIAL_H

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

#define DATA 0						// Data Register if DLAB = 0 | Baud Rate Divisor Least Significant Byte if DLAB = 1
#define INT_ENABLE 1				// Interrupt Enable Register if DLAB = 0 | Baud Rate Divisor Most Significant Byte if DLAB = 1
#define INT_ID_FIFO_CONTROL 2		// Interrupt Identification and FIFO Control Registers
#define LINE_CONTROL 3				// Line Control Register. Most Significant Bit = DLAB
#define MODEM_CONTROL 4				// Modem Control Register
#define LINE_STATUS 5				// Line Status Register
#define MODEM_STATUS 6				// Modem Status Register
#define SCRATCH 7					// Scratch Register

#endif
