#pragma once

#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "log_utils.h"

#include <openssl/ssl.h>
#include <openssl/err.h>
// #include <openssl/rsa.h>
// #include <openssl/x509.h>
// #include <openssl/evp.h>
#define MAXBUFFER 8192


SSL_CTX* mx_init_context(bool is_server);

void mx_use_certificate_key(SSL_CTX *ctx, char *certPath, char *keyPath);

SSL* mx_init_SSL_session(SSL_CTX* ctx, int socket);

void mx_SSL_log_print_error(SSL* ssl, int erno);

int mx_handshake(SSL* ssl, int is_server);

int mx_SSL_write(SSL* ssl, char* buffer);

int mx_SSL_read(SSL* ssl, char* buffer);

int mx_SSL_sendfile(SSL* ssl, char* filename);
int mx_SSL_readfile(SSL* ssl, char* filename);
