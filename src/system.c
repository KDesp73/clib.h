#include "system.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef _WIN32
CLIBAPI char* clib_system_execute_command(const char* command) {
    char buffer[128];
    char *result = NULL;
    size_t result_size = 0;
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        result = (char*) realloc(result, result_size + buffer_len + 1);
        if (!result) {
            pclose(pipe);
            return NULL;
        }
        strcpy(result + result_size, buffer);
        result_size += buffer_len;
    }

    pclose(pipe);
    return result;
}

CLIBAPI char* clib_system_get_env(const char* varname) {
    return getenv(varname);
}

CLIBAPI int set_envclib_(const char* varname, const char* value, int overwrite) {
    return setenv(varname, value, overwrite);
}

CLIBAPI int clib_system_unset_env(const char* varname) {
    return unsetenv(varname);
}

#endif
