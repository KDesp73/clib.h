#include "utils.h"
#include <stdio.h>

CLIBAPI int clib_eu_mod(int a, int b){
    if (b == 0) {
        // Handle division by zero case
        fprintf(stderr, "Error: Division by zero is undefined.\n");
        return 0;
    }
    
    int r = a % b;
    if (r < 0) {
        r += (b > 0) ? b : -b;
    }
    return r;
}
