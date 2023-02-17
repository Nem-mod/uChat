#include "../inc/server.h"


int main(int argc, char* argv[])
{
    
    if(argc != 2){
        mx_printerr("usage: ./uchat [port]\n");
        return 0;
    };

    
    sqlite3* db;
    char* db_name = "uchat.db";
    mx_openDB(db_name, &db);


    mx_initDB(db);
    //Insert new user in db ;
    // t_user* user = malloc(sizeof( t_user));
    // mx_strcpy(user->login, "nem");
    // mx_strcpy(user->password, "alocv");
    // mx_strcpy(user->nick_name, "nemdod");
    // mx_strcpy(user->first_name,"Artem");
    // mx_strcpy(user->last_name, "Necha");
    // user->user_id = mx_insert_user(db, user);

    char *ip = "127.0.0.1";
    int port = mx_atoi(argv[1]);

    SSL_CTX *ctx;
    ctx = create_context();

    //configure_context(ctx);
    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;
    pid = fork();// fork a new child process

    if (pid < 0)
    {
        mx_printerr("fork failed!\n");
        exit(1);
    }

    if (pid > 0)// its the parent process
    {
       mx_printstr("pid of child process: ");
       mx_printint(pid);
       mx_printstr("\n");
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

    

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    pid_t childpid;

    server_sock = Socket(AF_INET, SOCK_STREAM, 0);
    

    mx_memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    Bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    fp = fopen ("mydaemonfile.txt", "w+");
    Listen(server_sock, 5);
    while (1)
    {
        sleep(1);
        addr_size = sizeof(client_addr);
        //SSL *ssl;
        client_sock = Accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        //const char reply[] = "test\n";
        if ((childpid = fork()) == 0) 
        { 
            close(server_sock); 

            while (1)
            {
                // ssl = SSL_new(ctx);
                // SSL_set_fd(ssl, client_sock);

                // if (SSL_accept(ssl) <= 0) {
                //     ERR_print_errors_fp(stderr);
                // } else {
                //     SSL_write(ssl, reply, strlen(reply));
                // }

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
                //SSL_shutdown(ssl);
                //SSL_free(ssl);
                }

            }

        }

        
    }
    fclose(fp);
  
    return (0);
}
