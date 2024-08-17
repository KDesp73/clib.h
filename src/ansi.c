#include "ansi.h"
#include "strings.h"
#include <stdio.h>

CLIBAPI Cstr clib_ansi_color(int color, int bg) {
    if (color < 0 || color > 255) return "";

    char* where_code = ITOA(bg + 3);
    char* color_string = ITOA(color);

    char* color_str = clib_str_format("\e[%s8;5;%sm", where_code, color_string);
    free(where_code);
    free(color_string);
    return color_str;
}

CLIBAPI void clib_ansi_clear_screen() {
#ifdef _WIN32
    system("cls"); // Clear screen for Windows
#else
    system("clear"); // Clear screen for Linux and macOS
#endif
}


CLIBAPI void clib_ansi_print_color_table(){
    for(int i = 0; i < 256; i++){
        if(i % 21 == 0) printf("\n");
        
        printf("%s%3d ", clib_ansi_color(i, 0), i);
    }
    printf("%s\n", ANSI_RESET);
}
