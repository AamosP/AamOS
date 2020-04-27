/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/types.h>
#include <multiboot.h>
#include <stdarg.h>

char printbuf[1024];

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
void write_serial_str(char* a);

void console_init(multiboot_info_t *mbi, uint32_t fg, uint32_t bg);
void console_scroll(void);
void console_clear(void);
void console_putchar(char c);
void console_print(char* s);
uint64_t console_getcolor(uint32_t fg, uint32_t bg);
void console_setcolor(uint32_t fg, uint32_t bg);

void VGA_init(multiboot_info_t *mbi);
void VGA_putpixel(uint32_t x, uint32_t y, uint32_t color);
void VGA_drawrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void VGA_drawchar(uint32_t x, uint32_t y, uint32_t c, uint32_t fg_color, uint32_t bg_color);
void VGA_print(uint32_t x, uint32_t y, uint8_t* s, uint32_t fg_color, uint32_t bg_color);
void VGA_scroll(char d);
uint32_t VGA_getpixel(uint32_t x, uint32_t y);
void VGA_clear(void);

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

extern int vsprintf(char *buf, const char *fmt, va_list args);
extern int vprintf(const char *format, va_list args);
extern int printf(const char *format, ...);

void set_timer_freq(int hz);
void timer(void);

char get_queue(void);
void kb_init(void);
void kb_handler(int scancode);

#endif
