#include "logging.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

CLIBAPI void clib_log(int log_level, char* format, ...)
{
    switch(log_level){
    case CLIB_INFO:
        fprintf(stderr, "[INFO] ");
        break;
    case CLIB_WARN:
        fprintf(stderr, "[WARN] ");
        break;
    case CLIB_ERRO:
        fprintf(stderr, "[ERRO] ");
        break;
    case CLIB_DEBU:
        fprintf(stderr, "[DEBU] ");
        break;
    case CLIB_PANIC:
        fprintf(stderr, "[PANIC] ");
        break;
    default:
        assert(0 && "unreachable");
    }

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");

    if(log_level == CLIB_PANIC) exit(1);
}
