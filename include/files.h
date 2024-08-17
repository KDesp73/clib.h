#ifndef FILES_H
#define FILES_H

#include "api.h"
#include "types.h"

CLIBAPI int clib_file_create_directory(const char *path);
CLIBAPI int clib_file_directory_exists(const char *path);
CLIBAPI void clib_file_create(const char *filename);
CLIBAPI void clib_file_write(const char *filename, const char *data, Cstr mode);
CLIBAPI char* clib_file_read(const char *filename, const char* mode);
CLIBAPI void clib_file_delete(const char *filename);
CLIBAPI void clib_file_append(const char *filename, const char *data);
CLIBAPI void clib_file_copy(const char *source, const char *destination);
CLIBAPI void clib_file_move(const char *source, const char *destination);
CLIBAPI long clib_file_file(const char *filename);
CLIBAPI int clib_file_exists(const char *filename);

#endif // FILES_H
