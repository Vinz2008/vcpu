#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "context.h"

void error_and_exit(struct assembler_context* context, char* format, ...){
    va_list v;
    va_start(v, format);
    fprintf(stderr, "ERROR at line %d : ", context->line_nb);
    vfprintf(stderr, format, v);
    va_end(v);
    exit(1);
}