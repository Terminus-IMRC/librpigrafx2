/*
 * Copyright (c) 2017 Sugizaki Yukimasa (ysugi@idein.jp)
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

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

    putc('\n', stderr);
}
