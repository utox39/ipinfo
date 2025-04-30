#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

int remove_prefix(char* hex_ip_addr)
{
    char *prefix = strstr(hex_ip_addr, "0x");
    if (prefix == hex_ip_addr) {
        memmove(hex_ip_addr, hex_ip_addr + 2, strlen(hex_ip_addr) - 1);
        return 1;
    } else if (prefix != NULL) {
        fprintf(stderr, "ipinfo: invalid 0x position\n");
        return 0;
    }

    return 0;
}

int is_valid_hex(const char* hex_ip_addr)
{
    for (int i = 0; i < strlen(hex_ip_addr); i++) {
        if (!isxdigit(hex_ip_addr[i])) {
            return 0;
        }
    }

    return 1;
}

unsigned int parse_hex_address(const char* addr) {
    char* temp_hex_ip_addr = strdup(addr);
    if (temp_hex_ip_addr == NULL) {
        fprintf(stderr, "ipinfo: memory error\n");
        return -1;
    }

    if (remove_prefix(temp_hex_ip_addr) == 0){
        return -1;
    }

    if (!is_valid_hex(temp_hex_ip_addr)) {
        fprintf(stderr, "ipinfo: the string contains invalid hex digit/s.\n");
        return -1;
    }

    unsigned int ip_value = (unsigned int) strtoul(temp_hex_ip_addr, NULL, 16);

    free(temp_hex_ip_addr);

    return ip_value;
}

unsigned int parse_classic_address(const char* addr) {
    struct in_addr ip_bin;

    if (inet_pton(AF_INET, addr, &ip_bin) != 1) {
        perror("inet_pton");
        return -1;
    }

    unsigned int ip_value = ntohl(ip_bin.s_addr);

    return ip_value;
}
