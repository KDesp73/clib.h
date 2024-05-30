#define CLIB_IMPLEMENTATION
#include "../clib.h"

int main(){
    printf("%s\n", clib_execute_command("ls -a"));
    
    return 0;
}

