#pragma once

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "libmx.h"
#include "libdb.h"
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define SYSLOG "server_log.txt"
#define IP "127.0.0.1"
#define SERVER 1
#define CLIENT 0

int mx_create_socket(int domain, int type, int protocol);

void mx_bind_socket_to_address(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void mx_listen_socket(int sockfd, int backlog);

int mx_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

struct sockaddr_in mx_init_address(int port, char *ip, int family);

SSL_CTX* mx_init_context(bool is_server);

void mx_use_certificate_key(SSL_CTX *ctx, char *certPath, char *keyPath);

SSL* mx_init_SSL_session(SSL_CTX* ctx, int socket);

void mx_SSL_log_print_error(SSL* ssl, int erno);

int mx_handshake(SSL* ssl, int is_server);

int mx_SSL_write(SSL* ssl, char* buffer);

int mx_SSL_read(SSL* ssl, char* buffer);

void mx_init_daemon();

char* mx_get_formatted_time();

void mx_log_SSL_errors(char* file);

void mx_log_msg(char* file, char* str);

void mx_log_err(char* file, char* str);

void mx_log_info(char* file, char* str);
