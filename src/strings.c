#include "strings.h"
#include "logging.h"
#include <stdarg.h>
#include <string.h>
#include <assert.h>


CLIBAPI char* clib_str_buffer_init()
{
    char* buffer = (char*) malloc(1);
    memset(buffer, 0, 1);

    return buffer;
}

CLIBAPI void clib_str_append_ln(char** buffer, Cstr text)
{
    assert(buffer != NULL && *buffer != NULL);
    assert(text != NULL);

    Cstr new_text = clib_str_format("%s\n", text);
    size_t new_size = strlen(*buffer) + strlen(new_text) + 1;
    *buffer = (char*) realloc(*buffer, new_size);
    if (*buffer == NULL) {
        PANIC("Failed to reallocate memory");
    }
    strcat(*buffer, new_text);
    free((char*) new_text);
}

CLIBAPI void clib_str_append(char** buffer, const char* text)
{
    assert(buffer != NULL && *buffer != NULL);
    assert(text != NULL);

    size_t current_size = strlen(*buffer);
    size_t text_len = strlen(text);

    *buffer = (char*) realloc(*buffer, current_size + text_len + 1);
    if (*buffer == NULL) {
        PANIC("Failed to reallocate memory");
    }

    strcat(*buffer, text);
}

CLIBAPI void clib_str_clean(char** buffer)
{
    free(*buffer);
    *buffer = NULL;
}

CLIBAPI void println(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf(fmt, args);
    va_end(args);
}

CLIBAPI char* clib_str_format(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    size_t size = vsnprintf(NULL, 0, format, args) + 1; // +1 for the null terminator
    va_end(args);

    char* formatted_string = (char*) malloc(size);
    if (formatted_string == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(formatted_string, size, format, args);
    va_end(args);

    formatted_string[size-1] = '\0';

    return formatted_string;
}
