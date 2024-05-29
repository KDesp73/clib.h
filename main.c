#define CLIB_IMPLEMENTATION
#include "clib.h"

void demo_text(){
    print_color_table(); 
    printf("\n");
    printf("%s%s%s\n", COLOR_FG(25), "Blue text", RESET);
    printf("%s%s%s%s\n", COLOR_FG(25), ITALIC, "Blue and italic", RESET);
    printf("%s%s%s\n", ITALIC, "Just italic", RESET);
    printf("%s%s%s\n", BOLD, "Bold text", RESET);
    printf("%s%s%s\n", UNDERLINE, "Underlined text", RESET);
}

void demo_logs(){
    Cstr str = CONCAT("Hello", " World");
    INFO("%s", str);
    WARN("This is a warning");
    ERRO("An error");
    DEBU("a = 4");
    PANIC("panic here");
}

int main(int argc, char** argv){
    demo_text();
    printf("\n\n");
    demo_logs();

    return 0;
}
