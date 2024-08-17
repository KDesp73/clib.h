#ifndef STRINGS_H
#define STRINGS_H

#include "api.h"
#include "types.h"

#define ITOA(i) clib_str_format("%d", i) 
#define FTOA(f) clib_str_format("%f", f)
#define STR(x) #x
#define STREQ(x, y) (strcmp(x, y) == 0) 

CLIBAPI char* clib_str_format(const char *format, ...);
CLIBAPI char* clib_str_buffer_init();
CLIBAPI void clib_str_append_ln(char** buffer, Cstr text);
CLIBAPI void clib_str_append(char** buffer, const char* text);
CLIBAPI void clib_str_clean(char** buffer);
CLIBAPI void println(const char* fmt, ...);

#endif // STRINGS_H
