/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <stdarg.h>
#include <aamOS/kernel.h>
#include <printf.h>

int __printf(const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = __vsprintf(printbuf, format, arg);
	va_end(arg);

	write_string(printbuf);
	return done;
}
//extern __typeof (__printf) printf __attribute__ ((alias ("__printf")));
