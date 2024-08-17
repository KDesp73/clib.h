#ifndef SYSTEM_H
#define SYSTEM_H

#include "api.h"
#ifndef _WIN32
CLIBAPI char* clib_system_execute_command(const char* command);
CLIBAPI char* clib_system_get_env(const char* varname);
CLIBAPI int clib_system_set_env(const char* varname, const char* value, int overwrite);
CLIBAPI int clib_system_unset_env(const char* varname);
#endif

#endif // SYSTEM_H
