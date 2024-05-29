#define CLIB_IMPLEMENTATION
#include "../clib.h"

int main(){
    print_color_table(); 
    printf("\n");
    printf("%s%s%s\n", COLOR_FG(25), "Blue text", RESET);
    printf("%s%s%s%s\n", COLOR_FG(25), ITALIC, "Blue and italic", RESET);
    printf("%s%s%s\n", ITALIC, "Just italic", RESET);
    printf("%s%s%s\n", BOLD, "Bold text", RESET);
    printf("%s%s%s\n", UNDERLINE, "Underlined text", RESET);

    return 0;
}
