#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
