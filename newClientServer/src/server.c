#include <stdio.h>
#include "../inc/erproc.h"

int main() {
    int server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};

    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;

    ssize_t nread;
    char buf[256];

    /* Create a TLS server context with certificates */
    SSL_library_init();
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    ctx = SSL_CTX_new(TLS_server_method());
    if (ctx == NULL) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) <= 0)  {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) <= 0)  {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(55555);

    Bind(server_sock, (struct sockaddr *) &server_addr, sizeof server_addr);
    Listen(server_sock, 5);

    socklen_t server_addrlen = sizeof(server_addr);
    int client_sock = Accept(server_sock, (struct sockaddr *) &server_addr, &server_addrlen);

    /* Create an SSL session for the new socket */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_sock);

    int result = SSL_accept(ssl);

    if (result != 1) {
        switch(SSL_get_error(ssl, result)) {
            case SSL_ERROR_NONE:
            fprintf(stderr, "error SSL_ERROR_NONE\n");
            break;
            case SSL_ERROR_ZERO_RETURN:
            fprintf(stderr, "error SSL_ERROR_ZERO_RETURN \n");
            break;
            case SSL_ERROR_WANT_READ:
            fprintf(stderr, "error SSL_ERROR_WANT_READ\n");
            break;
            case SSL_ERROR_WANT_WRITE:
            fprintf(stderr, "error SSL_ERROR_WANT_WRITE\n");
            break;
            case SSL_ERROR_WANT_CONNECT:
            fprintf(stderr, "error SSL_ERROR_WANT_CONNECT\n");
            break;
            case SSL_ERROR_WANT_X509_LOOKUP:
            fprintf(stderr, "error SSL_ERROR_WANT_X509_LOOKUP\n");
            break;
            case SSL_ERROR_SYSCALL:
            fprintf(stderr, "error SSL_ERROR_SYSCALL\n");
            break;
            case SSL_ERROR_SSL:
            fprintf(stderr, "error SSL_ERROR_SSL\n");
            break;
            default:
            fprintf(stderr, "error f****** s***!!!\n");
            break;
        }
        fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
        ERR_print_errors_fp(stderr);
    } else {
        nread = SSL_read(ssl, buf, 256);
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            printf("END OF FILE occured\n");
        }
        write(STDOUT_FILENO, buf, nread);
        SSL_write(ssl, buf, nread);
    }
    

    // sleep(15);

    close(client_sock);
    close(server_sock);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}
