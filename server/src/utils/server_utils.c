#include "server.h"

int mx_init_daemon() {
    // pid_t pid;
    // struct rlimit flim;

    // if ((pid = fork()) < 0)
    //     return;
    // if (pid != 0) {
    //     printf("Daemon started with PID =%d\n", pid);
    //     exit(0);
    // }
    // setsid();
    // chdir("/");
    
    // getrlimit(RLIMIT_NOFILE, &flim);
    // for (rlim_t i = 0; i < flim.rlim_max; i++)
    //     close(i);
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

void* mx_create_server_client_session(void *server_ssl) {
    SSL *ssl = (SSL*)server_ssl;
    int hs_result;
    char buffer[MAXBUFFER];
    
    hs_result = mx_handshake(ssl, SERVER);
    if (hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            
            mx_SSL_read(ssl, buffer);
            mx_log_info(SYSLOG, "vvv Get JSON from the client vvv");
            mx_log_info(SYSLOG, buffer);

            

            if(mx_strcmp(buffer, ":exit") == 0)
                break;
            char* res = mx_strdup(main_handler(buffer));

            mx_SSL_write(ssl, res);
            mx_log_info(SYSLOG, "vvv Pass JSON to the client vvv");
            mx_log_info(SYSLOG, res);

            mx_strdel(&res);
        }
        
    }
    SSL_free(ssl);

    pthread_exit (0);
}
