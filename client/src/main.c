#include "../inc/client.h"

int main(int argc, char* argv[])
{
    if(argc != 2){
        mx_printerr("usage: ./uchat [port]\n");
        return 0;
    }

    char *ip = "127.0.0.1";
    int port = mx_atoi(argv[1]);
    int client_sock = Socket(AF_INET, SOCK_STREAM, 0);;
    struct sockaddr_in client_addr = {0};

    SSL_CTX *ctx;
    SSL *ssl = NULL;

    char buffer[1024];
    int result;

    /* Create a TLC client context with a CA certificate */
    SSL_library_init();
    ctx = SSL_CTX_new(TLS_client_method());
    SSL_CTX_use_certificate_file(ctx, "ca.srt", SSL_FILETYPE_PEM);

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &client_addr.sin_addr);

    /* Create SSL session */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_sock);

    result = connect(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if(result < 0) 
    {
        mx_printerr("[-] Error in connection\n");
        close(client_sock);
        exit(-1);
    }
    mx_printstr("Connected to the server.\n");

    /* Run the handshake */
    result = SSL_connect(ssl);
    // if (result != 1) {
    //     perror("handshake failed");
    //     exit(EXIT_FAILURE);
    // }

    while (1)
    {
        mx_memset(&buffer, 0, sizeof(buffer));


        mx_printstr("Client: ");
        scanf("%s", &buffer[0]);
        mx_printstr("\n");

        /* Writing to the SSL session */
        SSL_write(ssl, buffer, mx_strlen(buffer) + 1);

        if(strcmp(buffer, ":exit") == 0)
        {
            close(client_sock);
            mx_printerr("[-]Disconnected from server.\n");
            close(client_sock);
            break;
        }

        mx_memset(&buffer, 0, sizeof(buffer));
        if(SSL_read(ssl, buffer, sizeof(buffer)) < 0)
        {
            mx_printerr("[-]Error in receiving data.\n");
            exit(-1);

        } else {
            mx_printstr("Server:");
            mx_printstr(buffer);
            mx_printstr("\n");
        }
    }
    close(client_sock);
    SSL_free(ssl);
    SSL_CTX_free(ctx);  
    
    mx_printstr("Disconnected from the server.\n");

    return 0;
}
