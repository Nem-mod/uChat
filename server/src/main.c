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
    // t_user user, user2;
    // user.login = "nem";
    // user.password = "alocv";
    // user.nick_name = "nemdod";
    // user.first_name = "Artem";
    // user.last_name = "Necha";
    // user.user_id = mx_insert_user(db, &user);
    // user2.login = "dah";
    // user2.password = "alocv";
    // user2.nick_name = "nemdod";
    // user2.first_name = "Artem";
    // user2.last_name = "Necha";
    // user2.user_id = mx_insert_user(db, &user2);
    // mx_insert_contact(db, &user, &user2);

    // t_group gp;
    // gp.group_name = "mdod";
    // gp.group_id = mx_insert_group(db, &gp);
    // t_group_member gpm;
    // gpm.group_id = gp.group_id;
    // gpm.user_id = user.user_id;
    // gpm.group_member_id = mx_insert_group_member(db, &gp, &user);
    // t_message msg;
    // msg.message_text = "HAHHAHAHAHH AMOGUS GUS SUS";
    // msg.sent_datatime = "23-02-12 00:00:00";
    // msg.message_id = mx_insert_message(db, &gp, &gpm, &msg);
    // char *ip = "127.0.0.1";
    // int port = mx_atoi(argv[1]);

    //SSL_CTX *ctx;
    //ctx = create_context();

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
