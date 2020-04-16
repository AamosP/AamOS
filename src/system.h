#ifndef __SYSTEM_H
#define __SYSTEM_H

#define sti() __asm__ ("sti"::)

#include <multiboot2.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

/* KERNEL.C */
struct multiboot_tag* get_tag(uint32_t tag_type, unsigned long addr);

/* UTILS.C */
uint8_t inb(uint16_t __port);
void outb(uint16_t __port, uint8_t __value);
void itoa(char *buf, int base, int d);
int oct2bin(uint8_t *str, int size);
int printf(const char *format, ...);
uint32_t farpeekl(uint16_t sel, void* off);
void farpokeb(uint16_t sel, void* off, uint8_t v);
void io_wait(void);
void* memset(void* bufptr, int value, int size);
int puts(const char* string);
void putch(const char ch);
int kerror(const char* str);

/* VGA.C */
void VGA_init(struct multiboot_tag_framebuffer *tag);
void VGA_putpixel(uint32_t x, uint32_t y, uint32_t color);
void VGA_drawrect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void VGA_drawchar(uint32_t x, uint32_t y, uint32_t c, uint32_t fg_color, uint32_t bg_color);
void VGA_print(uint32_t x, uint32_t y, uint8_t* s, uint32_t fg_color, uint32_t bg_color);
void VGA_clear(void);

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

/* FONT.C */
char* get_font_data(uint32_t c);

/* CONSOLE.C */
void console_init(struct multiboot_tag_framebuffer *tag, uint32_t fg, uint32_t bg);
void console_clear(void);
void console_putchar(char c);
void console_print(char* s);
uint32_t fg_col;
uint32_t bg_col;

/* KEYBOARD.C */
void keyboard_handler(struct regs *r);
void kb_in(void);

/* SERIAL.C */
void init_serial(uint16_t port);
char read_serial();
void write_serial(char a);
void write_serial_str(char* a);

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

#define SERIAL_DATA 0						// Data Register if DLAB = 0 | Baud Rate Divisor Least Significant Byte if DLAB = 1
#define SERIAL_INT_ENABLE 1					// Interrupt Enable Register if DLAB = 0 | Baud Rate Divisor Most Significant Byte if DLAB = 1
#define SERIAL_INT_ID_FIFO_CONTROL 2		// Interrupt Identification and FIFO Control Registers
#define SERIAL_LINE_CONTROL 3				// Line Control Register. Most Significant Bit = DLAB
#define SERIAL_MODEM_CONTROL 4				// Modem Control Register
#define SERIAL_LINE_STATUS 5				// Line Status Register
#define SERIAL_MODEM_STATUS 6				// Modem Status Register
#define SERIAL_SCRATCH 7					// Scratch Register

/* IRQ.C */
uint8_t kbsc;

#endif
