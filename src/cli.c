#include "cli.h"
#include "safe-memory.h"
#include "logging.h"
#include "ansi.h"
#include <errno.h>
#include <stdarg.h>
#include <getopt.h>
#include <string.h>


CLIBAPI CliArg* clib_cli_create_argument(char abr, Cstr full, Cstr help, size_t argument_required)
{
    CliArg* arg = (CliArg*) clib_safe_malloc(sizeof(CliArg));

    if(full){
        arg->full = (char*) malloc(strlen(full) + 1);
        if (!arg->full) {
            free(arg);
            return NULL;
        }
        strcpy(arg->full, full);
    }

    arg->help = (char*) malloc(strlen(help) + 1);
    if (!arg->help) {
        free(arg->full);
        free(arg);
        return NULL;
    }
    strcpy(arg->help, help);

    arg->abr = abr;
    arg->argument_required = argument_required;

    return arg;
}

CLIBAPI void clib_cli_add_arg(CliArg* arg, CliArguments* arguments)
{
    if(arguments->capacity <= arguments->count) {
        ERRO("Max capacity");
        return;
    }

    arguments->args[arguments->count++] = arg;
}

CLIBAPI void clib_cli_clean_arguments(CliArguments* arguments)
{
    for(size_t i = 0; i < arguments->count; ++i){
        free(arguments->args[i]->full);
        free(arguments->args[i]->help);
        free(arguments->args[i]);
    }
    free(arguments->args);
}

CLIBAPI CliArguments clib_cli_make_arguments(size_t capacity, CliArg* first, ...)
{
    CliArguments arguments = { .capacity = capacity };

    arguments.args = (CliArg**) clib_safe_malloc(sizeof(arguments.args[0]) * arguments.capacity);
    
    if (arguments.args == NULL) {
        PANIC("could not allocate memory: %s", strerror(errno));
    }

    if(first == NULL) return arguments;

    arguments.args[arguments.count++] = first;

    va_list args;
    va_start(args, first);
    for (CliArg* next = va_arg(args, CliArg*); next != NULL; next = va_arg(args, CliArg*)) {
        if(arguments.capacity == arguments.count) break;
        arguments.args[arguments.count++] = next;
    }
    va_end(args);


    return arguments;
}

CLIBAPI struct option* clib_cli_get_options(CliArguments args)
{
    if (args.count == 0) {
        return NULL;
    }

    struct option* options = (struct option*) malloc(sizeof(struct option) * args.count);
    if (!options) {
        return NULL;
    }

    for (size_t i = 0; i < args.count; ++i) {
        CliArg* arg = args.args[i];
        options[i].val = arg->abr;
        if(arg->full) options[i].name = arg->full;
        options[i].flag = NULL;
        options[i].has_arg = arg->argument_required;
    }

    return options;
}

static size_t get_max_length(CliArguments args)
{
    size_t max_len = 0;

    for(size_t i = 0; i < args.count; ++i){
        if(args.args[i] == NULL) continue;

        size_t current_len = 0;
        if(args.args[i]->full == NULL)
            current_len = snprintf(NULL, 0, "-%c", args.args[i]->abr);
        else
            current_len = snprintf(NULL, 0, "-%c --%s", args.args[i]->abr, args.args[i]->full);
        if(current_len > max_len) max_len = current_len;
    }

    return max_len;
}

static char* add_spaces(size_t max_len, CliArg* arg)
{
    size_t arg_len = 0;
    if(arg->full == NULL)
        arg_len = snprintf(NULL, 0, "-%c", arg->abr);
    else 
         arg_len = snprintf(NULL, 0, "-%c --%s", arg->abr, arg->full);

    size_t GAP = 4;
    size_t final_size = max_len - arg_len + GAP + 1; // +1 for '\0'
    char* spaces = (char*) malloc(final_size);
    if(spaces == NULL){
        return NULL;
    }

    for(size_t i = 0; i < final_size - 1; ++i){
        spaces[i] = ' ';
    }
    spaces[final_size-1] = '\0';

    return spaces;
}

CLIBAPI void clib_cli_help(CliArguments args, Cstr usage, Cstr footer)
{
    if(usage) printf("Usage: %s\n\n", usage);

    size_t max_len = get_max_length(args);
    for(size_t i = 0; i < args.count; ++i){
        Cstr has_arg = NULL;
        switch(args.args[i]->argument_required){
            case no_argument:
                has_arg = "no argument";
                break;
            case required_argument:
                has_arg = "requires argument";
                break;
            case optional_argument:
                has_arg = "optional argument";
                break;
        }

        char* spaces = add_spaces(max_len, args.args[i]);
        if(spaces == NULL) return;
        Cstr arg_required = COLOR_FG(args.args[i]->argument_required + 1);
        if(args.args[i]->full){
            printf("-%c --%s%s%s %s[%s]%s\n", 
                args.args[i]->abr, 
                args.args[i]->full,
                spaces,
                args.args[i]->help,
                arg_required,
                has_arg,
                ANSI_RESET
            );
        } else {
            printf("-%c%s%s %s[%s]%s\n", 
                args.args[i]->abr, 
                spaces,
                args.args[i]->help,
                arg_required,
                has_arg,
                ANSI_RESET
            );
        }
        free((char*) arg_required);
        free(spaces);
    }
    printf("\n");

    if(footer) printf("%s\n", footer);
}

CLIBAPI char* clib_cli_generate_format_string(CliArguments args)
{
    size_t length = 1;
    for (size_t i = 0; i < args.count; ++i) {
        length += 1;
        if (args.args[i]->argument_required) {
            length += 1;
        }
    }

    char* fmt = (char*) malloc(length * sizeof(char));
    if (!fmt) {
        return NULL;
    }

    fmt[0] = '\0';

    for (size_t i = 0; i < args.count; ++i) {
        char abr[2] = {args.args[i]->abr, 0};
        if(args.args[i]->argument_required == optional_argument) strcat(fmt, ":");
        strcat(fmt, abr);
        if (args.args[i]->argument_required) strcat(fmt, ":");
    }
    strcat(fmt, "\0");

    return fmt;
}
