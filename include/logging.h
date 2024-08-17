#ifndef LOGGING_H
#define LOGGING_H

#include "api.h"
#include <stdio.h>

#define HANDLE_ERROR(msg) \
    do { \
        perror(CONCAT("[ERRO] ", msg)); \
        printf("\n"); \
        exit(1); \
    } while (0) \

typedef enum {
    CLIB_INFO,
    CLIB_WARN,
    CLIB_ERRO,
    CLIB_DEBU,
    CLIB_PANIC,
} ClibLog;

CLIBAPI void clib_log(int log_level, char* format, ...);

#define LOG(stream, type, format, ...) \
    do { \
        fprintf(stream, "[%s] ", type); \
        fprintf(stream, format, ##__VA_ARGS__); \
        fprintf(stream, "\n"); \
    } while(0)

#define INFO(format, ...) \
    LOG(stdout, "INFO", format, ##__VA_ARGS__)

#define ERRO(format, ...) \
    LOG(stderr, "ERRO", format, ##__VA_ARGS__)

#define WARN(format, ...) \
    LOG(stderr, "WARN", format, ##__VA_ARGS__)

#ifdef DEBUG
    #define DEBU(format, ...) \
        LOG(stderr, "DEBU", format, ##__VA_ARGS__)
#else
    #define DEBU(format, ...) 
#endif // DEBUG

#define PANIC(format, ...)                            \
    do {                                              \
        LOG(stderr, "PANIC", format, ##__VA_ARGS__);  \
        exit(1);                                      \
    } while(0)

#define DEMO(expr)                    \
    do {                              \
        LOG(stdout, "DEMO", #expr);   \
        expr;                         \
    } while(0)

#endif // LOGGING_H
