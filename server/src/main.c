#include "../inc/server.h"

int main(int argc, char* argv[])
{
    if(argc != 2){
        mx_printerr("usage: ./uchat [port]\n");
        return 0;
    }

    char *ip = "127.0.0.1";
    int port = mx_atoi(argv[1]);
    int server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};

    SSL_CTX *ctx;
    SSL *ssl;

    FILE *fp = NULL;
    char buffer[1024];
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_pton(ip);

    Bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    Listen(server_sock, 5);

    fp = fopen ("mydaemonfile.txt", "w+");
    while (1) {
        pid_t childpid;
        int client_sock = Accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        struct sockaddr_in client_addr = {0};
        socklen_t addr_size = sizeof(client_addr);
        
        if ((childpid = fork()) == 0)  { 
            close(server_sock); 

            while (1) {
                mx_memset(&buffer, 0, sizeof(buffer));
                recv(client_sock, buffer, sizeof(buffer), 0);

                mx_printstr(buffer);
                if(mx_strlen(buffer) != 0) {   
                    fprintf(fp, "Client: %s\n", buffer);
                }
                if(mx_strcmp(buffer, ":exit") == 0)  {
                    close(client_sock);
                    break;
                }
                send(client_sock, buffer, strlen(buffer), 0);
            }
        }
    }
    fclose(fp);
  
    return (0);
}
