#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include "../libs/libmx/inc/libmx.h"

#include <stdint.h>
#include "json.h"

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

const char *message_get_message(json_object *message);
const char *message_get_datetime(json_object *message);
// const char *time_to_string(struct tm tm);
