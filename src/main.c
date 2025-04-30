#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "ip_info.h"

int main(int argc, char* argv[])
{
    unsigned int ip_value;

    unsigned int (*parse_fn)(const char*) = parse_args(argc, argv);
    if (parse_fn == NULL) {
        return EXIT_FAILURE;
    }

    ip_value = parse_fn(argv[2]);

    if (ip_value == -1) {
        return EXIT_FAILURE;
    }

    char *ip = to_ip_addr(ip_value);
    if (ip == NULL) {
        return EXIT_FAILURE;
    }

    printf("> IP Address: %s\n", ip);
    printf("> IP Class: %c\n", get_address_class(ip_value));
    printf("> Is up: %s\n",
        is_host_up(ip, 22, 1) ? "Yes - Port 22 is open"
        : is_host_up(ip, 80, 1) ? "Yes - Port 80 is open"
        : is_host_up(ip, 443, 1) ? "Yes - Port 443 is open"
        : is_host_up(ip, 3389, 1) ? "Yes - Port 3389 is open"
        : is_host_up(ip, 135, 1) ? "Yes - Port 135 is open"
        : is_host_up(ip, 445, 1) ? "Yes - Port 445 is open"
        : is_host_up(ip, 8080, 1) ? "Yes - Port 8080 is open" : "No"
    );

    free(ip);

    return 0;
}
