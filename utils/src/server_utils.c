#include "../inc/server_utils.h"

void mx_init_daemon() {
    pid_t pid;
    struct rlimit flim;

    if ((pid = fork()) < 0)
        return;
    if (pid != 0) {
        printf("Daemon started with PID =%d\n", pid);
        exit(0);
    }
    setsid();
    chdir("/");
    
    getrlimit(RLIMIT_NOFILE, &flim);
    for (rlim_t i = 0; i < flim.rlim_max; i++)
        close(i);
}

void* mx_create_server_client_session(void *server_ssl) {
    SSL *ssl = (SSL*)server_ssl;
    int hs_result;
    char buffer[2048];
    
    hs_result = mx_handshake(ssl, SERVER);
    if (hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            
            mx_SSL_read(ssl, buffer);

            mx_log_msg(SYSLOG, buffer);

            if(mx_strcmp(buffer, ":exit") == 0)
                break;

            mx_SSL_write(ssl, buffer);
        }
    }
    SSL_free(ssl);

    pthread_exit (0);
}
