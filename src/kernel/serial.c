#include <aamOS/kernel.h>
#include <asm/io.h>
#include <printf.h>

static uint16_t PORT;

void init_serial(uint16_t port) {
	if ((port == COM1) | (port == COM2) | (port == COM3) | (port == COM4)) {
		PORT = port;
		outb((uint16_t)(PORT + 1), 0x00);    // Disable all interrupts
		outb((uint16_t)(PORT + 3), 0x80);    // Enable DLAB (set baud rate divisor)
		outb((uint16_t)(PORT + 0), 0x01);    // Set divisor to 1 (lo byte) 38400 baud
		outb((uint16_t)(PORT + 1), 0x00);    //                  (hi byte)
		outb((uint16_t)(PORT + 3), 0x03);    // 8 bits, no parity, one stop bit
		outb((uint16_t)(PORT + 2), 0xC7); // Enable FIFO, clear them, with 14-byte threshold
		outb((uint16_t)(PORT + 4), 0x0B);    // IRQs enabled, RTS/DSR set
	} else {
		printf("Invalid Port: 0x%x\n", port);
		return;
	}
}

static int serial_received(void) {
	return inb((uint16_t)(PORT + 5)) & 1;
}

uint8_t read_serial() {
	while (serial_received() == 0)
		;
	return inb(PORT);
}

static int is_transmit_empty(void) {
	return inb((uint16_t)(PORT + 5)) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0)
		;

	outb(PORT, (uint8_t)a);
}

void write_serial_str(char *a) {
	int i = 0;
	while (a[i]) {
		write_serial(a[i]);
		i++;
	}
}
