#pragma once

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>

#include "log_utils.h"

int mx_create_socket(int domain, int type, int protocol);

void mx_bind_socket_to_address(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void mx_listen_socket(int sockfd, int backlog);

int mx_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

struct sockaddr_in mx_init_address(int port, char *ip, int family);
