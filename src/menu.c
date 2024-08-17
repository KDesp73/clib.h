#include "menu.h"
#include "ansi.h"
#include "logging.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define CLIB_MENUS
#ifdef CLIB_MENUS
#ifndef _WIN32
    int _getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

CLIBAPI void clib_enable_input_buffering(){
    #ifdef _WIN32
        // Enable console input buffering
        HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

        DWORD consoleMode;
        GetConsoleMode(hConsoleInput, &consoleMode);

        consoleMode |= ENABLE_LINE_INPUT;

        SetConsoleMode(hConsoleInput, consoleMode);
    #else
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

    #endif
    ANSI_SHOW_CURSOR();
}

CLIBAPI void clib_disable_input_buffering(){
    #ifdef _WIN32
        // Disable console input buffering
        DWORD mode;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hInput, &mode);
        SetConsoleMode(hInput, mode & ~ENABLE_ECHO_INPUT & ~ENABLE_LINE_INPUT);
    #else
        struct termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

    #endif
    ANSI_HIDE_CURSOR();
}

CLIBAPI int clib_getch() {
    int ch;
    #ifdef _WIN32
        ch = _getch();
        if (ch == 0 || ch == 224) {
            // Handle extended keys (arrows, function keys)
            ch = _getch();
            switch (ch) {
                case 72: return CLIB_KEY_ARROW_UP;
                case 80: return CLIB_KEY_ARROW_DOWN;
                case 75: return CLIB_KEY_ARROW_LEFT;
                case 77: return CLIB_KEY_ARROW_RIGHT;
                default: return CLIB_KEY_UNKNOWN;
            }
        }
    #else
        ch = _getch();
        if (ch == 27) {
            if (getchar() == '[') {
                switch (getchar()) {
                    case 'A': return CLIB_KEY_ARROW_UP;
                    case 'B': return CLIB_KEY_ARROW_DOWN;
                    case 'C': return CLIB_KEY_ARROW_RIGHT;
                    case 'D': return CLIB_KEY_ARROW_LEFT;
                    default: return CLIB_KEY_UNKNOWN;
                }
            }
            return CLIB_KEY_ESC;
        }
    #endif

    switch (ch) {
        case 10: return CLIB_KEY_ENTER;
        case 127: return CLIB_KEY_BACKSPACE;
        case 9: return CLIB_KEY_TAB;
        case 27: return CLIB_KEY_ESC;
        case 32: return CLIB_KEY_SPACE;
        case '0': return CLIB_KEY_0;
        case '1': return CLIB_KEY_1;
        case '2': return CLIB_KEY_2;
        case '3': return CLIB_KEY_3;
        case '4': return CLIB_KEY_4;
        case '5': return CLIB_KEY_5;
        case '6': return CLIB_KEY_6;
        case '7': return CLIB_KEY_7;
        case '8': return CLIB_KEY_8;
        case '9': return CLIB_KEY_9;
        case 'A': return CLIB_KEY_A;
        case 'B': return CLIB_KEY_B;
        case 'C': return CLIB_KEY_C;
        case 'D': return CLIB_KEY_D;
        case 'E': return CLIB_KEY_E;
        case 'F': return CLIB_KEY_F;
        case 'G': return CLIB_KEY_G;
        case 'H': return CLIB_KEY_H;
        case 'I': return CLIB_KEY_I;
        case 'J': return CLIB_KEY_J;
        case 'K': return CLIB_KEY_K;
        case 'L': return CLIB_KEY_L;
        case 'M': return CLIB_KEY_M;
        case 'N': return CLIB_KEY_N;
        case 'O': return CLIB_KEY_O;
        case 'P': return CLIB_KEY_P;
        case 'Q': return CLIB_KEY_Q;
        case 'R': return CLIB_KEY_R;
        case 'S': return CLIB_KEY_S;
        case 'T': return CLIB_KEY_T;
        case 'U': return CLIB_KEY_U;
        case 'V': return CLIB_KEY_V;
        case 'W': return CLIB_KEY_W;
        case 'X': return CLIB_KEY_X;
        case 'Y': return CLIB_KEY_Y;
        case 'Z': return CLIB_KEY_Z;
        case 'a': return CLIB_KEY_a;
        case 'b': return CLIB_KEY_b;
        case 'c': return CLIB_KEY_c;
        case 'd': return CLIB_KEY_d;
        case 'e': return CLIB_KEY_e;
        case 'f': return CLIB_KEY_f;
        case 'g': return CLIB_KEY_g;
        case 'h': return CLIB_KEY_h;
        case 'i': return CLIB_KEY_i;
        case 'j': return CLIB_KEY_j;
        case 'k': return CLIB_KEY_k;
        case 'l': return CLIB_KEY_l;
        case 'm': return CLIB_KEY_m;
        case 'n': return CLIB_KEY_n;
        case 'o': return CLIB_KEY_o;
        case 'p': return CLIB_KEY_p;
        case 'q': return CLIB_KEY_q;
        case 'r': return CLIB_KEY_r;
        case 's': return CLIB_KEY_s;
        case 't': return CLIB_KEY_t;
        case 'u': return CLIB_KEY_u;
        case 'v': return CLIB_KEY_v;
        case 'w': return CLIB_KEY_w;
        case 'x': return CLIB_KEY_x;
        case 'y': return CLIB_KEY_y;
        case 'z': return CLIB_KEY_z;
        // Add other mappings as needed
        default: return CLIB_KEY_UNKNOWN;
    }
}


CLIBAPI void clib_default_print_option(Cstr option, int is_selected, int color){
    is_selected ? printf("%s%s%s", COLOR_BG(color), option, ANSI_RESET) : printf("%s", option);
}

CLIBAPI void clib_arrow_print_option(Cstr option, int is_selected, int color){
    is_selected ? printf("%s>%s %s", COLOR_FG(color), ANSI_RESET, option) : printf("  %s", option);
}

CLIBAPI void clib_brackets_print_option(Cstr option, int is_selected, int color){
    is_selected ? printf("%s[%s%s%s]%s", COLOR_FG(color), ANSI_RESET, option, COLOR_FG(color), ANSI_RESET) : printf(" %s ", option);
}

CLIBAPI int clib_menu(Cstr title, int color, ClibPrintOptionFunc print_option, Cstr first_option, ...){
    clib_disable_input_buffering();

    int selected = 0;
    size_t size = 0;
    CstrArray options = {0};

    if (first_option == NULL) {
        return -1;
    }

    va_list args;
    va_start(args, first_option);
    options.count++;
    Cstr next = NULL;
    for (next = va_arg(args, Cstr); next != NULL; ) {
        next = va_arg(args, Cstr);
        if(next)
            options.count++;
    }
    va_end(args);

    options.items = (Cstr*) malloc(sizeof(options.items[0]) * options.count);
    if (options.items == NULL) {
        PANIC("could not allocate memory: %s", strerror(errno));
    }
    options.count = 0;

    options.items[options.count++] = first_option;

    va_start(args, first_option);
    next = NULL;
    for (next = va_arg(args, Cstr); next != NULL;) {
        options.items[options.count] = next;
        next = va_arg(args, Cstr);
        if(next != NULL) options.count++;
    }

    va_end(args);

    while(1){
        if(title != NULL){
            printf("%s%s%s\n", COLOR_FG(color), title, ANSI_RESET);
        }
        for(size_t i = 0; i < options.count; ++i){
            print_option(options.items[i], selected == i, color);
            printf("\n");
        }
        
        int pressed = clib_getch();
        switch (pressed) {
            case CLIB_KEY_ARROW_UP:
                selected = clib_eu_mod((selected-1), options.count);
                break;
            case CLIB_KEY_ARROW_DOWN:
                selected = clib_eu_mod((selected+1), options.count);
                break;
            case CLIB_KEY_ENTER:
                clib_enable_input_buffering();
                free(options.items);
                return selected; 
            default:
                break;
        }

        ANSI_MOVE_CURSOR_UP(options.count + (title != NULL));
        ANSI_CLEAR_BELOW_CURSOR;
    }
}
#endif // CLIB_MENUS
