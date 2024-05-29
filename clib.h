/*
 * MIT License
 * 
 * Copyright (c) 2024 Konstantinos Despoinidis
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Usage: 
 * #define CLIB_IMPLEMENTATION
 * #inlcude "clib.h"
*/


#ifndef CLIB_H
#define CLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#ifndef _WIN32
#define PATH_SEP "/"
#else 
#define PATH_SEP "\\"
#endif // _WIN32

// START [TYPES] START //
typedef const char * Cstr;

typedef struct {
    Cstr* items;
    size_t count;
} CstrArray;
// END [TYPES] END//

// START [DECLARATIONS] START //

CstrArray cstr_array_make(Cstr first, ...);
Cstr cstr_array_join(Cstr sep, CstrArray cstrs);

#define true 1
#define false 0
#define BOOL(x) x ? "true" : "false"

// ANSI
#define RESET "\e[0;39m"
#define BOLD "\e[1m"
#define UNDERLINE "\033[4m"
#define ITALIC "\e[3m"
#define CLEAR "\e[2J"
#define ERASE_LINE "\e[2K"
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"

Cstr color(int color, int bg);
void clearScreen();
void print_color_table();

#define COLOR_BG(c) color(c, 1)
#define COLOR_FG(c) color(c, 0)

// FILES
void create_file(const char *filename);
void write_file(const char *filename, const char *data);
char* read_file(const char *filename);
void delete_file(const char *filename);
void append_file(const char *filename, const char *data);
void copy_file(const char *source, const char *destination);
void move_file(const char *source, const char *destination);
long file_size(const char *filename);
int file_exists(const char *filename);

// UTILS
char* shift_args(int *argc, char ***argv);
#define ITOA(s, i) sprintf(s, "%d", i);
#define JOIN(sep, ...) cstr_array_join(sep, cstr_array_make(__VA_ARGS__, NULL))
#define CONCAT(...) JOIN("", __VA_ARGS__)
#define PATH(...) JOIN(PATH_SEP, __VA_ARGS__)

// LOGGING
#define LOG(stream, type, format, ...) \
    fprintf(stream, CONCAT("[%s] ", format, "\n"), type, ##__VA_ARGS__)

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
// END [DECLARATIONS] END//

// START [IMPLEMENTATIONS] START //
#ifdef CLIB_IMPLEMENTATION
CstrArray cstr_array_make(Cstr first, ...) {
    CstrArray result = {0};

    if (first == NULL) {
        return result;
    }

    result.count += 1;

    va_list args;
    va_start(args, first);
    for (Cstr next = va_arg(args, Cstr); next != NULL; next = va_arg(args, Cstr)) {
        result.count += 1;
    }
    va_end(args);

    result.items = (Cstr*) malloc(sizeof(result.items[0]) * result.count);
    if (result.items == NULL) {
        PANIC("could not allocate memory: %s", strerror(errno));
    }
    result.count = 0;

    result.items[result.count++] = first;

    va_start(args, first);
    for (Cstr next = va_arg(args, Cstr); next != NULL; next = va_arg(args, Cstr)) {
        result.items[result.count++] = next;
    }
    va_end(args);

    return result;
}

Cstr cstr_array_join(Cstr sep, CstrArray cstrs) {
    if (cstrs.count == 0) {
        return "";
    }

    const size_t sep_len = strlen(sep);
    size_t len = 0;
    for (size_t i = 0; i < cstrs.count; ++i) {
        len += strlen(cstrs.items[i]);
    }

    const size_t result_len = (cstrs.count - 1) * sep_len + len + 1;
    char *result = malloc(sizeof(char) * result_len);
    if (result == NULL) {
        PANIC("could not allocate memory: %s", strerror(errno));
    }

    len = 0;
    for (size_t i = 0; i < cstrs.count; ++i) {
        if (i > 0) {
            memcpy(result + len, sep, sep_len);
            len += sep_len;
        }

        size_t elem_len = strlen(cstrs.items[i]);
        memcpy(result + len, cstrs.items[i], elem_len);
        len += elem_len;
    }
    result[len] = '\0';

    return result;
}

char* shift_args(int *argc, char ***argv) {
    assert(*argc > 0);
    char *result = **argv;
    *argc -= 1;
    *argv += 1;
    return result;
}

Cstr color(int color, int bg) {
    if (color < 0 || color > 255) return "";

    char where_code[12], color_string[12];
    ITOA(where_code, bg + 3);
    ITOA(color_string, color);

    return CONCAT("\e[", where_code, "8;5;", color_string, "m");
}

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Clear screen for Windows
#else
    system("clear"); // Clear screen for Linux and macOS
#endif
}


void print_color_table(){
    for(int i = 0; i < 256; i++){
        if(i % 21 == 0) printf("\n");
        
        printf("%s%3d ", color(i, 0), i);
    }
    printf("%s\n", RESET);
}


void copy_file(const char *source, const char *destination) {
    FILE *srcFile = fopen(source, "r");
    if (srcFile == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *destFile = fopen(destination, "w");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(srcFile);
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, destFile) != bytesRead) {
            perror("Error writing to destination file");
            fclose(srcFile);
            fclose(destFile);
            exit(EXIT_FAILURE);
        }
    }

    fclose(srcFile);
    fclose(destFile);
}

void move_file(const char *source, const char *destination) {
    if (rename(source, destination) != 0) {
        perror("Error moving/renaming file");
        exit(EXIT_FAILURE);
    }
}

long file_size(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void append_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }
    if (fputs(data, file) == EOF) {
        perror("Error appending to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void write_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    if (fputs(data, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

char* read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, file_size, file);
    if (bytesRead != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}

void delete_file(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }
}
#endif // CLIB_IMPLEMENTATION
// END [IMPLEMENTATIONS] END//



#endif // CLIB_H

