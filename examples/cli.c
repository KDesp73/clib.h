#define CLIB_IMPLEMENTATION
#include "../clib.h"


int main(int argc, char** argv){
    CliArguments args = clib_make_cli_arguments(3, NULL);

    clib_add_arg(clib_create_argument('h', NULL, "Prints this message", no_argument), &args);
    clib_add_arg(clib_create_argument('v', "version", "Prints the version of the program", optional_argument), &args);
    clib_add_arg(clib_create_argument('f', "file", "Specify the file to parse", required_argument), &args);

    struct option* options = clib_get_options(args);

    int opt;
	while ((opt = getopt_long(argc, argv, clib_generate_cli_format_string(args), options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                clib_cli_help(args, CONCAT(argv[0], " [-h | -v] -f <file>"), "Made by KDesp73");
                exit(0);
            case 'v':
                printf("v0.0.1\n");
                exit(0);
            case 'f':
                INFO("File found: %s", optarg);
                break;
            default:
                exit(1);
        }
    }


    return 0;
}
