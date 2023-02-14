#include "../inc/server.h"

int main(int argc, char* argv[])
{
    if(argc != 2){
        mx_printerr("usage: ./uchat_server [port]\n");
        return 0;
    }

    char *ip = "127.0.0.1";
    int port = mx_atoi(argv[1]);
    int server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};

    SSL_CTX *ctx;
    SSL *ssl = NULL;

    FILE *fp = NULL;
    char buffer[1024];
    
    /* Create a TLC server context with certificates */
    SSL_library_init();
    ctx = SSL_CTX_new(TLS_server_method());
    SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM);
    SSL_use_PrivateKey_file(ssl, "server.key", SSL_FILETYPE_PEM);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    Bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    Listen(server_sock, 5);

    fp = fopen ("mydaemonfile.txt", "w+");
    while (1) {
        pid_t childpid;
        struct sockaddr_in client_addr = {0};
        socklen_t addr_size = sizeof(client_addr);
        int client_sock = Accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        int hs_result;
        
        if ((childpid = fork()) == 0)  { 
            close(server_sock);
            /* Create an SSL session for the new socket */
            ssl = SSL_new(ctx);
            SSL_set_fd(ssl, client_sock); 

            /* Run the handshake */
            hs_result = SSL_accept(ssl);
            // if (hs_result != 1) {
            //     perror("handshake failed");
            //     exit(EXIT_FAILURE);
            // }

            while (1) {
                mx_memset(&buffer, 0, sizeof(buffer));
                
                /* Reading from the SSL session */
                SSL_read(ssl, buffer, sizeof(buffer));
                // recv(client_sock, buffer, sizeof(buffer), 0);

                mx_printstr(buffer);
                if(mx_strlen(buffer) != 0) {   
                    fprintf(fp, "Client: %s\n", buffer);
                }
                if(mx_strcmp(buffer, ":exit") == 0)  {
                    close(client_sock);
                    break;
                }

                /* Writing to the SSL session */
                SSL_write(ssl, buffer, mx_strlen(buffer) + 1);
                // send(client_sock, buffer, strlen(buffer), 0);
            }
            close(client_sock);
            SSL_free(ssl);
            SSL_CTX_free(ctx);
        }
    }
    fclose(fp);
  
    return (0);
}
