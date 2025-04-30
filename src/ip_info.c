#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "ip_info.h"

char* to_ip_addr(unsigned int ip_value)
{
    char buffer[15];
    int written = snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u",
               (ip_value >> 24) & 0xFF,
               (ip_value >> 16) & 0xFF,
               (ip_value >> 8) & 0xFF,
               ip_value & 0xFF
    );

    if (written < 0 || written >= sizeof(buffer)) {
        return NULL;
    }

    char *ip = (char*) malloc((written + 1) * sizeof(char));
    if (ip == NULL) return NULL;

    memcpy(ip, buffer, written);
    ip[written] = '\0';

    return ip;
}

char get_address_class(unsigned int ip_value)
{
    unsigned int first_octet = (ip_value >> 24) & 0xFF;

    if (first_octet <= 127)
        return 'A';
    else if (first_octet <= 191)
        return 'B';
    else if (first_octet <= 223)
        return 'C';
    else if (first_octet <= 239)
        return 'D';
    else
        return 'E';
}

int is_host_up(const char* ip, int port, int timeout_sec)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return 0;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
        perror("inet_pton");
        return 0;
    }

    // Sets the timeout
    struct timeval timeout;
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    int result = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    close(sock);

    return result == 0;
}
