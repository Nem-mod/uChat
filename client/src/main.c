#include "../inc/client.h"

int main(int argc, char* argv[])
{
    remove(SYSLOG);
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat [port]");
        return 0;
    }

    char *ip    = IP;
    int port    = mx_atoi(argv[1]);
    int client_sock;
    struct sockaddr_in client_addr = {0};

    SSL_CTX *ctx    = NULL;
    SSL *ssl        = NULL;

    char buffer[2048];
    int hs_result;

    client_sock = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    client_addr = mx_init_address(port, ip, AF_INET);
    // mx_bind_socket_to_address(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr));

    /* Create a TLC client context with a CA certificate */
    ctx = mx_init_context(CLIENT);
    mx_use_certificate_key(ctx, "client/cert+key/client.crt", "client/cert+key/client.key");
    // mx_use_certificate_key(ctx, "cert+key/client.crt", "cert+key/client.key");


    /* Create SSL session */
    ssl = mx_init_SSL_session(ctx, client_sock);

    mx_connect(client_sock, (struct sockaddr*)&client_addr, sizeof(client_addr));

    /* Run the handshake */
    hs_result = mx_handshake(ssl, CLIENT);

    while (1)
    {
        // mx_memset(&buffer, 0, sizeof(buffer));

        mx_printstr("Client: ");
        scanf("%s", &buffer[0]);
        mx_printstr("\n");

        /* Writing to the SSL session */
        mx_SSL_write(ssl, buffer);

        if(strcmp(buffer, ":exit") == 0)
        {
            close(client_sock);
            mx_printerr("[-]Disconnected from server.\n");
            close(client_sock);
            break;
        }

        mx_memset(&buffer, 0, sizeof(buffer));
        mx_SSL_read(ssl, buffer);

        mx_printstr("Server:");
        mx_printstr(buffer);
        mx_printstr("\n");
    }
    close(client_sock);
    SSL_free(ssl);
    SSL_CTX_free(ctx);  
    
    mx_printstr("Disconnected from the server.\n");

    return 0;
}
