#include <stdlib.h>#include <stdio.h>#include <stdarg.h>voidpm_error(char *format, ...){	va_list args;	va_start(args, format);	vfprintf(stderr, format, args);	exit(1);}#include "mppm3.c"