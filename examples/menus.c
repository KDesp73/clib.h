#define CLIB_IMPLEMENTATION
#define CLIB_MENUS
#include "../clib.h"

int main(void){
    int choice = clib_menu("Title", 1, clib_brackets_print_option, "Option 1", "Option 2", "Option 3", "Option 4");
    INFO("choice: %d", choice);

    return 0;
}
