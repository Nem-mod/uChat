#include "../inc/server.h"


int main(int argc, char* argv[])
{
    
    if(argc != 2){
        mx_printerr("usage: ./uchat [port]\n");
        return 0;
    };
    char *ip = "127.0.0.1";
    int port = mx_atoi(argv[1]);

    
    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;
    pid = fork();// fork a new child process

    if (pid < 0)
    {
        mx_printstr("fork failed!\n");
        exit(1);
    }

    if (pid > 0)// its the parent process
    {
       mx_printstr("pid of child process");
       mx_printint(pid);
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
    

    mx_memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    Bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    

    Listen(server_sock, 5);
    printf("Listening...\n");
    while (1)
    {
        sleep(1);
        addr_size = sizeof(client_addr);
        client_sock = Accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

        mx_memset(&buffer, 0, sizeof(buffer));
        recv(client_sock, buffer, sizeof(buffer), 0);

        mx_memset(&buffer, 0, sizeof(buffer));
        mx_strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
    }
    fclose(fp);
  
    return (0);
}
