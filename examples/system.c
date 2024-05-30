#define CLIB_IMPLEMENTATION
#include "../clib.h"

int main(){
    printf("%s\n", clib_execute_command("ls -a"));
    
    INFO("%s", clib_get_env("HOME"));
    
    return 0;
}

