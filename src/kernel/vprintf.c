/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <stdarg.h>
#include <aamOS/kernel.h>
#include <printf.h>

int
__vprintf (const char *format, va_list args)
{
  int done;

  done = __vsprintf (printbuf, format, args);

  console_print (printbuf);
  return done;
}
extern __typeof (__vprintf) vprintf __attribute__ ((alias ("__vprintf")));
