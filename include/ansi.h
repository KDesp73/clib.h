#ifndef ANSI_H
#define ANSI_H

#include "api.h"
#include "types.h"
#define ANSI_RESET "\e[0;39m"
#define ANSI_BOLD "\e[1m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_ITALIC "\e[3m"
#define ANSI_CLEAR "\e[2J"
#define ANSI_ERASE_LINE "\e[2K"
#define ANSI_HIDE_CURSOR() printf("\e[?25l")
#define ANSI_SHOW_CURSOR() printf("\e[?25h")
#define ANSI_GOTOXY(x,y) printf("\033[%d;%dH", (y), (x))
#define ANSI_MOVE_CURSOR_UP(x) printf("\033[%zuA", x)
#define ANSI_MOVE_CURSOR_DOWN(x) printf("\033[%dB", x);
#define ANSI_MOVE_CURSOR_RIGHT(x) printf("\033[%dC", x);
#define ANSI_MOVE_CURSOR_LEFT(x) printf("\033[%dD", x);
#define ANSI_CLEAR_BELOW_CURSOR printf("\033[J")

#define ANSI_BLACK "\e[0;30m"
#define ANSI_RED "\e[0;31m"
#define ANSI_GREEN "\e[0;32m"
#define ANSI_YELLOW "\e[0;33m"
#define ANSI_BLUE "\e[0;34m"
#define ANSI_PURPLE "\e[0;35m"
#define ANSI_CYAN "\e[0;36m"
#define ANSI_LGREY "\e[0;37m"
#define ANSI_DGREY "\e[0;38m"

CLIBAPI Cstr clib_ansi_color(int color, int bg);
CLIBAPI void clib_ansi_clear_screen();
CLIBAPI void clib_ansi_print_color_table();

#define COLOR_BG(c) clib_ansi_color(c, 1)
#define COLOR_FG(c) clib_ansi_color(c, 0)

#endif // ANSI_H
