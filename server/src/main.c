#include "../inc/server.h"


int main(int argc, char* argv[])
{
    
    if(argc != 2){
        printf("%s", "usage: ./uchat [port]\n");
        return 0;
    };
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    
    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;
    pid = fork();// fork a new child process

    if (pid < 0)
    {
        printf("fork failed!\n");
        exit(1);
    }

    if (pid > 0)// its the parent process
    {
       printf("pid of child process %d \n", pid);
        exit(0); //terminate the parent process succesfully
    }

    umask(0);//unmasking the file mode

    sid = setsid();//set new session
    if(sid < 0)
    {
        exit(1);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    fp = fopen ("mydaemonfile.txt", "w+");

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];

    server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    
    printf("[+]TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    Bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    printf("[+]Bind to the port number: %d\n", port);

    Listen(server_sock, 5);
    printf("Listening...\n");
    while (1)
    {
        sleep(1);
        addr_size = sizeof(client_addr);
        client_sock = Accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("[+]Client connected.\n");

        memset(&buffer, 0, sizeof(buffer));
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        memset(&buffer, 0, sizeof(buffer));
        strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
        printf("Server: %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
        printf("[+]Client disconnected.\n\n");
    }
    fclose(fp);
  
    return (0);
}
