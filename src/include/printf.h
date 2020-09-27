/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdarg.h>

static char printbuf[1024];

int __vsprintf(char *buf, const char *fmt, va_list args);
int __vprintf(const char *format, va_list args);
int __sprintf(char *s, const char *format, ...);
int __printf(const char *format, ...);

const auto vsprintf = __vsprintf;
const auto vprintf = __vprintf;
const auto sprintf = __sprintf;
const auto printf = __printf;

#endif
