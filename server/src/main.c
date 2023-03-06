#include "../inc/server.h"

static int create_daemon() {
    pid_t pid = 0;
    pid_t sid = 0;
    pid = fork();

    if (pid < 0)
    {
        mx_log_info(SYSLOG, "fork failed!\n");
        return 1; 
    }

    if (pid > 0)
    {
       mx_log_info(SYSLOG, "pid of child process\n");
       return 1; 
    }

    umask(0);

    sid = setsid();
    if(sid < 0)
    {
        return 1; 
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    return 0;
}
int main(int argc, char* argv[])
{
    remove(SYSLOG);
    
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat_server [port]");
        return 0;
    }

    // Create daemon process

    if(create_daemon() == 1) {
        exit(1);
    }
    // Init DAYABASE

    sqlite3* db;
    char* db_name = "uchat.db";
    mx_openDB(db_name, &db);
    mx_initDB(db);

    //
    
    char *ip    = IP;
    int port    = mx_atoi(argv[1]);
    int server_sock;
    struct sockaddr_in server_addr;
    //char buffer[1024];

    SSL_CTX *ctx    = NULL;
    SSL *ssl        = NULL;

    server_sock = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    server_addr = mx_init_address(port, ip, AF_INET);
    mx_bind_socket_to_address(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    mx_listen_socket(server_sock, 5);

    ctx = mx_init_context(SERVER);
    mx_use_certificate_key(ctx, CERTPATH, KEYPATH);

    while (1) {
        pthread_t thread_id;
        struct sockaddr_in client_addr;
        socklen_t addr_size = sizeof(client_addr);
        int client_sock     = mx_accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        
        ssl = mx_init_SSL_session(ctx, client_sock);
        pthread_create(&thread_id, NULL, mx_create_server_client_session, (void*)ssl);
            
        
    }

    close(server_sock);
    SSL_CTX_free(ctx);
  
    return (0);
}
