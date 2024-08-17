#ifndef SAFE_MEMORY_H
#define SAFE_MEMORY_H

#include <stdlib.h>
#include "api.h"

CLIBAPI void* clib_safe_malloc(size_t size);
CLIBAPI void* clib_safe_calloc(size_t nmemb, size_t size);
CLIBAPI void* clib_safe_realloc(void *ptr, size_t size);
CLIBAPI void clib_safe_free(void **ptr);

#endif // SAFE_MEMORY_H
