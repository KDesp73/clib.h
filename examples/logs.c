#define CLIB_IMPLEMENTATION
#include "../clib.h"


int main(int argc, char** argv){
    Cstr str = CONCAT("Hello", " World");
    INFO("%s", str);
    WARN("This is a warning");
    ERRO("An error");
    DEBU("a = 4");
    PANIC("panic here");

    return 0;
}
