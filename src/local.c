#include "rpigrafx.h"
#include "local.h"
#include <stdio.h>
#include <stdarg.h>

void print_error_core(const char *file, const int line, const char *func,
                      const char *fmt, ...)
{
    va_list ap;

    fprintf(stderr, "%s:%d:%s: ", file, line, func);

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}
