#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef _WIN32
    #define PATH_SEP "/"
#else 
    #define PATH_SEP "\\"
#endif // _WIN32

#define true 1
#define false 0
#define BOOL(x) (x ? "true" : "false")

#endif // CONSTANTS_H
