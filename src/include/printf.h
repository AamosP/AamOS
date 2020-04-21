#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdarg.h>

char printbuf[1024];

int vsprintf(char *buf, const char *fmt, va_list args);
int vprintf(const char *format, va_list args);
int sprintf(char *s, const char *format, ...);
int printf(const char *format, ...);

#endif
