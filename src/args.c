#include <stdio.h>
#include <string.h>

#include "args.h"
#include "parser.h"

// Returns a pointer to a function (unsigned int fn(char* foo))
unsigned int (*parse_args(int argc, char* argv[])) (const char*) {
    if (argc != 3) {
        fprintf(stderr, "%s: invalid args number.\n", argv[0]);
        return NULL;
    }

    if (strcmp(argv[1], "-x") == 0) {
        return parse_hex_address;
    } else if (strcmp(argv[1], "-a") == 0) {
        return parse_classic_address;
    } else {
        fprintf(stderr, "%s: unknown argument.\n", argv[0]);
        return NULL;
    }
}
