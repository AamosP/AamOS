/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

extern int vsprintf(char *buf, const char *fmt, va_list args);
extern int vprintf(const char *format, va_list args);
extern int sprintf(char *s, const char *format, ...);
extern int printf(const char *format, ...);

#endif
