#include "../inc/server.h"

int mx_create_socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);

    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    return res;
}

void mx_bind_socket_to_address(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);

    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void mx_listen_socket(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);

    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int mx_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);

    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    return res;
}

struct sockaddr_in mx_init_address(int port, char *ip, int family) {
    struct sockaddr_in addr = {0};

    addr.sin_family = family;
    addr.sin_port = htons(port);
    inet_pton(family, ip, &addr.sin_addr);

    return addr;
}

SSL_CTX* mx_init_context(bool is_server) {
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    if (is_server)
        ctx = SSL_CTX_new(TLS_server_method());
    else
        ctx = SSL_CTX_new(TLS_client_method());

    if (ctx == NULL) {
        perror("Unable to create SSL context"); // Write in daemon file (need to create special function or already exist)
        ERR_print_errors_fp(stderr);            // Same
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void mx_use_certificate_key(SSL_CTX *ctx, char *certPath, char *keyPath) {
    if (SSL_CTX_use_certificate_file(ctx, certPath, SSL_FILETYPE_PEM) <= 0) {
        perror("Unable to get certificate");    // Write in daemon file (need to create special function or already exist)
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, keyPath, SSL_FILETYPE_PEM) <= 0)  {
        perror("Unable to get private key");    // Write in daemon file (need to create special function or already exist)
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (!SSL_CTX_check_private_key(ctx)) {
        perror("Private key does not match the public certificate\n");  // Write in daemon file (need to create special function or already exist)
        exit(EXIT_FAILURE);
    }
}

SSL* mx_init_SSL_session(SSL_CTX* ctx, int socket) {
    SSL* ssl;

    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        perror("Unable to create SSL structure");    // Write in daemon file (need to create special function or already exist)
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_set_fd(ssl, socket) == 0) {
        perror("Unable to link socket to SSL session");    // Write in daemon file (need to create special function or already exist)
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ssl;
}

void mx_SSL_print_error(SSL* ssl, int erno) {    // Write in daemon file (need to create special function or already exist)
    if (erno != 1) {
        switch(SSL_get_error(ssl, erno)) {
            case SSL_ERROR_NONE:
                perror("error SSL_ERROR_NONE\n");
                break;
            case SSL_ERROR_SSL:
                perror("error SSL_ERROR_SSL\n");
                break;
            case SSL_ERROR_WANT_READ:
                perror("error SSL_ERROR_WANT_READ\n");
                break;
            case SSL_ERROR_WANT_WRITE:
                perror("error SSL_ERROR_WANT_WRITE\n");
                break;
            case SSL_ERROR_WANT_X509_LOOKUP:
                perror("error SSL_ERROR_WANT_X509_LOOKUP\n");
                break;
            case SSL_ERROR_SYSCALL:
                perror("error SSL_ERROR_SYSCALL\n");
                break;
            case SSL_ERROR_ZERO_RETURN:
                perror("error SSL_ERROR_ZERO_RETURN \n");
                break;
            case SSL_ERROR_WANT_CONNECT:
                perror("error SSL_ERROR_WANT_CONNECT\n");
                break;
            default:
                perror("error wtf\n");
                break;
        }
        ERR_print_errors_fp(stderr);
    }
}

int mx_handshake(SSL* ssl) {    // Write in daemon file (need to create special function or already exist)
    int result = SSL_accept(ssl);

    if (result != 1) {
        perror("Handshake error");    // Write in daemon file (need to create special function or already exist)
        mx_SSL_print_error(ssl, result);

        return 0;
    }
    return 1;
}

int mx_SSL_write(SSL* ssl, char* buffer) {
    int result;

    result = SSL_write(ssl, buffer, mx_strlen(buffer) + 1);
    if (result <= 0) {
        perror("Unable to write msg");    // Write in daemon file (need to create special function or already exist)
        mx_SSL_print_error(ssl, result);
    }

    return result;
}

int mx_SSL_read(SSL* ssl, char* buffer) {
    int result;

    result = SSL_read(ssl, buffer, sizeof(buffer));
    if (result <= 0) {
        perror("Unable to read msg");    // Write in daemon file (need to create special function or already exist)
        mx_SSL_print_error(ssl, result);
    }

    return result;
}
