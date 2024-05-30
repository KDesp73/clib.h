#define CLIB_IMPLEMENTATION
#include "../clib.h"

int main(int argc, char** argv){
    clib_shift_args(&argc, &argv);
    char* buffer = clib_read_file(argv[0]);

    printf("%s\n", buffer);
    
    return 0;
}
