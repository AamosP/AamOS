#include <stdarg.h>
#include <aamOS/kernel.h>
#include <printf.h>

int vprintf(const char *format, va_list args)
{
	int done;

	done = vsprintf(printbuf, format, args);

	return done;
}
