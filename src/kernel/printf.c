#include <stdarg.h>
#include <aamOS/kernel.h>
#include <printf.h>

int printf(const char *format, ...)
{
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(printbuf, format, arg);
	va_end(arg);

	console_print(printbuf);
	return done;
}
