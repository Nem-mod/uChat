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

unsigned int mx_handle_post_file(char* req, char** filename) {
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jtype = json_object_object_get(jobj, "type");
    mx_log_info(SYSLOG, (req));
    if(mx_strcmp(json_object_get_string(jtype), "POST-FILE")){
        return 0;
    }

    struct json_object *jfilename = json_object_object_get(jobj, "filename");
    *filename = (char*)json_object_get_string(jfilename);
    struct json_object *jsize = json_object_object_get(jobj, "size");
    mx_log_info(SYSLOG, (req));
    return json_object_get_uint64(jsize);
}

void* mx_create_server_client_session(void *server_ssl) {
    SSL *ssl = (SSL*)server_ssl;
    int hs_result;
    char buffer[MAXBUFFER];
    int file_flag = 0;
    char* filename = NULL;
    hs_result = mx_handshake(ssl, SERVER);
    int filesize;
    if (hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            switch (file_flag)
            {
            case 0:
                mx_SSL_read(ssl, buffer);
                mx_log_info(SYSLOG, buffer);
                break;
            
            case 1:
                mx_SSL_readfile(ssl, mx_strjoin("res/" , filename), filesize);
                file_flag = 0;
                mx_log_info(SYSLOG, mx_itoa(file_flag));
                // mx_log_info(SYSLOG, mx_itoa(file_flag));
                continue;
                break;
            }
            
            if(mx_strcmp(buffer, ":exit") == 0)
                break;
            
            if((filesize = mx_handle_post_file(buffer, &filename)) > 0) {
                file_flag = 1;
                mx_log_info(SYSLOG, mx_itoa(file_flag));
                continue;
            }
            
            // mx_log_info(SYSLOG, "vvv Pass JSON to the client vvv");
            mx_log_info(SYSLOG, (char*)main_handler(ssl, buffer));

        }
        
    }
    SSL_free(ssl);

    pthread_exit (0);
}
