#pragma once

#include <unistd.h>

#include "server_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"
#include "libdb.h"
#include <sys/time.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "json.h"


<<<<<<< HEAD
int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);


SSL_CTX *create_context();

void configure_context(SSL_CTX *ctx);
=======
#define IP "127.0.0.1"
#define CERTPATH "server/cert+key/server.crt"
#define KEYPATH "server/cert+key/server.key"
>>>>>>> SSL+Refactoring
