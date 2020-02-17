#ifndef UTILS_H
#define UTILS_H

extern __inline unsigned char inb(unsigned short int __port);
extern __inline void outb(unsigned char __value, unsigned short int __port);
extern void itoa(char *buf, int base, int d);

#endif
