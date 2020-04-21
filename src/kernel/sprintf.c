#include <stdarg.h>
#include <printf.h>

int sprintf(char *s, const char *format, ...) {
	va_list arg;
	int done;

	va_start(arg, format);
	done = vsprintf(s, format, arg);
	va_end(arg);

	return done;
}
