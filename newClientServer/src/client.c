#include "../inc/erproc.h"

int main() {
    
    int client_sock = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr = {0};

    char buf[256];
    ssize_t nread;
    int result;

    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;

    /* Create a TLS client context with a CA certificate */
    SSL_library_init();
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_certificate_file(ctx, "sa.crt", SSL_FILETYPE_PEM) <= 0)  {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "sa.key", SSL_FILETYPE_PEM) <= 0)  {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }


    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(55555);
    Inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr);

    connect(client_sock, (struct sockaddr *)&client_addr, sizeof(client_addr));

    /* Create an SSL session */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_sock);
    result = SSL_connect(ssl);
    if (result == -1) {   /* perform the connection */
        printf("SSL socket err\n");
        ERR_print_errors_fp(stderr);
    }

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
        SSL_write(ssl, "Hello\n", 6);
        nread = SSL_read(ssl, buf, 256);
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            printf("EOF occured\n");
        }
        write(STDOUT_FILENO, buf, nread);
    }

    // sleep(10);

    close(client_sock);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}
