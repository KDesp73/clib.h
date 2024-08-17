#ifndef UTILS_H
#define UTILS_H

#include "api.h"
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
#define SWAP(x, y) do { \
    typeof(x) temp = x; \
    x = y; \
    y = temp; \
} while (0)

#if defined(__GNUC__) || defined(__clang__)
    #define LIKELY(x) __builtin_expect(!!(x), 1)
#else
    #define LIKELY(x) (x)
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define UNLIKELY(x) (x)
#endif

CLIBAPI int clib_eu_mod(int a, int b);

#endif // UTILS_H
