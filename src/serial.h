#ifndef SERIAL_H
#define SERIAL_H

#include <utils.h>

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8
#define PORT COM1

void init_serial();
char read_serial();
void write_serial(char a);

#endif
