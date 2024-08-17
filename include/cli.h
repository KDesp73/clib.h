#ifndef CLI_H
#define CLI_H

#include "api.h"
#include "types.h"
#define LOOP_ARGS(opt, args) \
    while((opt = getopt_long(argc, argv, clib_cli_generate_format_string(args), clib_cli_get_options(args), NULL)) != -1)

CLIBAPI char* clib_cli_shift_args(int *argc, char ***argv);
CLIBAPI CliArg* clib_cli_create_argument(char abr, Cstr full, Cstr help, size_t argument_required);
CLIBAPI void clib_cli_clean_arguments(CliArguments* arguments);
CLIBAPI void clib_cli_add_arg(CliArg* arg, CliArguments* arguments);
CLIBAPI CliArguments clib_cli_make_arguments(size_t capacity, CliArg* first, ...);
CLIBAPI struct option* clib_cli_get_options(CliArguments args);
CLIBAPI char* clib_cli_generate_format_string(CliArguments args);
CLIBAPI void clib_cli_help(CliArguments args, Cstr usage, Cstr footer);

#endif // CLI_H

