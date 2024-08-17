#ifndef MENU_H
#define MENU_H

#include "api.h"
#include "types.h"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    int _getch();
#endif

// TODO: Add more keys
typedef enum {
    CLIB_KEY_UNKNOWN = -1,
    CLIB_KEY_ENTER = 10,
    CLIB_KEY_BACKSPACE = 127,
    CLIB_KEY_TAB = 9,
    CLIB_KEY_ESC = 27,
    CLIB_KEY_SPACE = 32,
    CLIB_KEY_0 = '0',
    CLIB_KEY_1 = '1',
    CLIB_KEY_2 = '2',
    CLIB_KEY_3 = '3',
    CLIB_KEY_4 = '4',
    CLIB_KEY_5 = '5',
    CLIB_KEY_6 = '6',
    CLIB_KEY_7 = '7',
    CLIB_KEY_8 = '8',
    CLIB_KEY_9 = '9',
    CLIB_KEY_A = 'A',
    CLIB_KEY_B = 'B',
    CLIB_KEY_C = 'C',
    CLIB_KEY_D = 'D',
    CLIB_KEY_E = 'E',
    CLIB_KEY_F = 'F',
    CLIB_KEY_G = 'G',
    CLIB_KEY_H = 'H',
    CLIB_KEY_I = 'I',
    CLIB_KEY_J = 'J',
    CLIB_KEY_K = 'K',
    CLIB_KEY_L = 'L',
    CLIB_KEY_M = 'M',
    CLIB_KEY_N = 'N',
    CLIB_KEY_O = 'O',
    CLIB_KEY_P = 'P',
    CLIB_KEY_Q = 'Q',
    CLIB_KEY_R = 'R',
    CLIB_KEY_S = 'S',
    CLIB_KEY_T = 'T',
    CLIB_KEY_U = 'U',
    CLIB_KEY_V = 'V',
    CLIB_KEY_W = 'W',
    CLIB_KEY_X = 'X',
    CLIB_KEY_Y = 'Y',
    CLIB_KEY_Z = 'Z',
    CLIB_KEY_a = 'a',
    CLIB_KEY_b = 'b',
    CLIB_KEY_c = 'c',
    CLIB_KEY_d = 'd',
    CLIB_KEY_e = 'e',
    CLIB_KEY_f = 'f',
    CLIB_KEY_g = 'g',
    CLIB_KEY_h = 'h',
    CLIB_KEY_i = 'i',
    CLIB_KEY_j = 'j',
    CLIB_KEY_k = 'k',
    CLIB_KEY_l = 'l',
    CLIB_KEY_m = 'm',
    CLIB_KEY_n = 'n',
    CLIB_KEY_o = 'o',
    CLIB_KEY_p = 'p',
    CLIB_KEY_q = 'q',
    CLIB_KEY_r = 'r',
    CLIB_KEY_s = 's',
    CLIB_KEY_t = 't',
    CLIB_KEY_u = 'u',
    CLIB_KEY_v = 'v',
    CLIB_KEY_w = 'w',
    CLIB_KEY_x = 'x',
    CLIB_KEY_y = 'y',
    CLIB_KEY_z = 'z',
    // Defined later
    CLIB_KEY_ARROW_UP,
    CLIB_KEY_ARROW_DOWN,
    CLIB_KEY_ARROW_LEFT,
    CLIB_KEY_ARROW_RIGHT
} ClibKey;

typedef void (*ClibPrintOptionFunc)(Cstr option, int is_selected, int color);
CLIBAPI void clib_default_print_option(Cstr option, int is_selected, int color);
CLIBAPI void clib_arrow_print_option(Cstr option, int is_selected, int color);
CLIBAPI void clib_brackets_print_option(Cstr option, int is_selected, int color);
CLIBAPI void clib_enable_input_buffering();
CLIBAPI void clib_disable_input_buffering();
CLIBAPI int clib_getch();
CLIBAPI int clib_menu(Cstr title, int color, ClibPrintOptionFunc print_option, Cstr first_option, ...);

#endif // MENU_H
