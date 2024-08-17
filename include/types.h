#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdint.h>

typedef const char * Cstr;
typedef uint8_t Bool;

typedef struct {
    Cstr* items;
    size_t count;
} CstrArray;

typedef struct {
    char* help;
    char* full;
    char abr;
    size_t argument_required;
} CliArg;

typedef struct {
    CliArg** args;
    size_t count;
    size_t capacity;
} CliArguments;


#endif // TYPES_H
