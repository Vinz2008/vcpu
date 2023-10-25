#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern int line_nb;


void error_and_exit(char* format, ...){
    va_list v;
    va_start(v, format);
    printf("ERROR at line %d : ", line_nb);
    vfprintf(stderr, format, v);
    va_end(v);
    exit(1);
}