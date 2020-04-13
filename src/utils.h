#ifndef UTILS_H
#define UTILS_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

unsigned char inb(unsigned short int __port);
void outb(uint16_t __port, uint8_t __value);
void itoa(char *buf, int base, int d);
int oct2bin(unsigned char *str, int size);
void print(unsigned char* str, unsigned int x, unsigned int y, uint64_t color);
uint32_t farpeekl(uint16_t sel, void* off);
void farpokeb(uint16_t sel, void* off, uint8_t v);
void io_wait(void);
void* memset(void* bufptr, int value, int size);

#endif
