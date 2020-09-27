/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/types.h>
#include <idt.h>
#include <stdarg.h>
#include <asm/io.h>
#include <asm/system.h>

#define WHITE 0xffffff
#define LIGHT_GRAY 0xc0c0c0
#define DARK_GRAY 0x808080
#define BLACK 0x000000
#define RED 0xff0000
#define DARK_RED 0x800000
#define YELLOW 0xffff00
#define BROWN 0x808000
#define GREEN 0x00ff00
#define DARK_GREEN 0x008000
#define CYAN 0x00ffff
#define DARK_CYAN 0x008080
#define BLUE 0x0000ff
#define DARK_BLUE 0x000080
#define MAGENTA 0xff00ff
#define PURPLE 0x800080

#define EGA_BLACK 0

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

#define SERIAL_DATA 0						/* Data Register if DLAB = 0 | Baud Rate Divisor Least Significant Byte if DLAB = 1 */
#define SERIAL_INT_ENABLE 1					/* Interrupt Enable Register if DLAB = 0 | Baud Rate Divisor Most Significant Byte if DLAB = 1 */
#define SERIAL_INT_ID_FIFO_CONTROL 2		/* Interrupt Identification and FIFO Control Registers */
#define SERIAL_LINE_CONTROL 3				/* Line Control Register. Most Significant Bit = DLAB */
#define SERIAL_MODEM_CONTROL 4				/* Modem Control Register */
#define SERIAL_LINE_STATUS 5				/* Line Status Register */
#define SERIAL_MODEM_STATUS 6				/* Modem Status Register */
#define SERIAL_SCRATCH 7					/* Scratch Register */

void init_serial(uint16_t port);
uint8_t read_serial(void);
void write_serial(char a);
void write_serial_str(const char* a);

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
void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
void dump_struct(void* structure, size_t bytes);

void set_timer_freq(int hz);
void timer(registers_t *regs);
void timer_init(void);

char get_queue(void);
void kb_init(void);
void kb_handler(registers_t *regs);

void idt_set_gate (uint8_t num, uint32_t offset, uint16_t sel, uint8_t flags);

void register_isr_handler(int n, void (*h)(registers_t*));
void init_isrs(void);

void register_irq_handler(int n, void (*h)(registers_t*));
void init_irqs(void);

void set_fg(uint8_t fg);
void set_bg(uint8_t bg);
void write_char(const char c);
void write_string(const char* s);

#endif
