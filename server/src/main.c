#include "../inc/server.h"

int main(int argc, char* argv[])
{
    remove(SYSLOG);
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat_server [port]");
        return 0;
    }

    char *ip    = IP;
    int port    = mx_atoi(argv[1]);
    int server_sock;
    struct sockaddr_in server_addr;

    SSL_CTX *ctx    = NULL;
    SSL *ssl        = NULL;

    char buffer[2048];

    server_sock = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    server_addr = mx_init_address(port, ip, AF_INET);
    mx_bind_socket_to_address(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    mx_listen_socket(server_sock, 5);

    /* Create a TLC server context with certificates */
    ctx = mx_init_context(SERVER);
    mx_use_certificate_key(ctx, "server/cert+key/server.crt", "server/cert+key/server.key");
    // mx_use_certificate_key(ctx, "cert+key/server.crt", "cert+key/server.key");

    while (1) {
        pid_t childpid;
        struct sockaddr_in client_addr;
        socklen_t addr_size = sizeof(client_addr);
        int client_sock = mx_accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        int hs_result;
        
        if ((childpid = fork()) == 0)  { 
            close(server_sock);

            /* Create an SSL session for the new socket */
            ssl = mx_init_SSL_session(ctx, client_sock);

            /* Run the handshake */
            hs_result = mx_handshake(ssl, SERVER);
            if (hs_result == 0) {
                // SLL_free(ssl);
                exit(EXIT_FAILURE);
            }

            while (1) {
                mx_memset(&buffer, 0, sizeof(buffer));
                
                /* Reading from the SSL session */
                mx_SSL_read(ssl, buffer);

                mx_log_msg(SYSLOG, buffer);

                if(mx_strcmp(buffer, ":exit") == 0)
                    break;

                /* Writing to the SSL session */
                mx_SSL_write(ssl, buffer);
            }
            close(client_sock);
            SSL_free(ssl);
            SSL_CTX_free(ctx);
        }
    }

    close(server_sock);
    SSL_CTX_free(ctx);
  
    return (0);
}
