#ifndef IP_INFO_H
#define IP_INFO_H

char* to_ip_addr(unsigned int ip_value);
char get_address_class(unsigned int ip_value);
int is_host_up(const char* ip, int port, int timeout_sec);

#endif
