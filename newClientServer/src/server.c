#include <stdio.h>
#include "erproc.h"

#include "../inc/server.h"

int main(int argc, char* argv[])
{
    char *ip = "127.0.0.1";
    int server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    struct server_addr_in server addr;

    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
// =============================================================================
    char *ip = "127.0.0.1";
    int port = mx_atoi(argv[argc - 1]);
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    pid_t childpid;

    server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    

    mx_memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip); // Avoid using inet_addr (man inet_addr)

    Bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    Listen(server_sock, 5);
    while (1)
    {
        sleep(1);
        addr_size = sizeof(client_addr);
        client_sock = Accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        if ((childpid = fork()) == 0) 
        { 
            close(server_sock); 

            while (1)
            {
                mx_memset(&buffer, 0, sizeof(buffer));
                recv(client_sock, buffer, sizeof(buffer), 0);

                mx_printstr(buffer);
                if(mx_strlen(buffer) != 0)
                {   
                    fprintf(fp, "Client: %s\n", buffer);
                }
                if(mx_strcmp(buffer, ":exit") == 0) 
                {
                    close(client_sock);
                    break;
                } else {

                send(client_sock, buffer, strlen(buffer), 0);
                mx_memset(&buffer, 0, sizeof(buffer));
                }

            }

        }

        
    }
    fclose(fp);
  
    return (0);
}


// int main() {
//     OPENSSL_init();
//     int server = Socket(AF_INET, SOCK_STREAM, 0);
//     struct sockaddr_in adr = {0};
//     adr.sin_family = AF_INET;
//     adr.sin_port = htons(34543);
//     Bind(server, (struct sockaddr *) &adr, sizeof adr);
//     Listen(server, 5);
//     socklen_t adrlen = sizeof adr;
//     int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
//     ssize_t nread;
//     char buf[256];
//     nread = read(fd, buf, 256);
//     if (nread == -1) {
//         perror("read failed");
//         exit(EXIT_FAILURE);
//     }
//     if (nread == 0) {
//         printf("END OF FILE occured\n");
//     }
//     write(STDOUT_FILENO, buf, nread);
//     write(fd, buf, nread);

//     sleep(15);

//     close(fd);
//     close(server);
//     return 0;
// }
