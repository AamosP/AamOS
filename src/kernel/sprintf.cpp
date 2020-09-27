/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <stdarg.h>
#include <printf.h>

int __sprintf(char *s, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = __vsprintf(s, format, arg);
	va_end(arg);

	return done;
}
//extern __typeof (__sprintf) sprintf __attribute__ ((alias ("__sprintf")));
