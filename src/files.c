#include "files.h"
#include "logging.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

CLIBAPI void clib_file_copy(const char *source, const char *destination) {
    FILE *srcFile = fopen(source, "r");
    if (srcFile == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *destFile = fopen(destination, "w");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(srcFile);
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, destFile) != bytesRead) {
            perror("Error writing to destination file");
            fclose(srcFile);
            fclose(destFile);
            exit(EXIT_FAILURE);
        }
    }

    fclose(srcFile);
    fclose(destFile);
}

CLIBAPI void clib_file_move(const char *source, const char *destination) {
    if (rename(source, destination) != 0) {
        perror("Error moving/renaming file");
        exit(EXIT_FAILURE);
    }
}

CLIBAPI long clib_file_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

CLIBAPI int clib_file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

CLIBAPI void clib_file_append(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }
    if (fputs(data, file) == EOF) {
        perror("Error appending to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0755) // 0755 is the permission mode
#endif

CLIBAPI int clib_file_create_directory(const char *path)
{
    if (MKDIR(path) == 0) {
        return 1;
    } else {
        if (errno == EEXIST) {
            printf("Directory already exists: %s\n", path);
        } else {
            perror("Error creating directory");
        }
        return 0; 
    }
}

CLIBAPI int clib_file_directory_exists(const char *path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0) {
        return 0;
    }

    return S_ISDIR(statbuf.st_mode);
}

CLIBAPI void clib_file_create(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

CLIBAPI void clib_file_write(const char *filename, const char *data, Cstr mode) {
    if(
        strcmp(mode, "w") &&
        strcmp(mode, "w+") &&
        strcmp(mode, "wb") &&
        strcmp(mode, "a") &&
        strcmp(mode, "ab") &&
        strcmp(mode, "a+")
    ) {
        PANIC("Writing file using invalid mode: %s", mode);
    }

    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    if (fputs(data, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

CLIBAPI char* clib_file_read(const char *filename, const char* mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, file_size, file);
    if (bytesRead != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}

CLIBAPI void clib_file_delete(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }
}
