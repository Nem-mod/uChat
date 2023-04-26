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
        //mx_log_info(SYSLOG, "fork failed!\n");
        return 1; 
    }

    if (pid > 0)
    {
       //mx_log_info(SYSLOG, "pid of child process\n");
       return 1; 
    }
   
    
    umask(0);

    sid = setsid();
    mx_printstr("PID: ");
    mx_printint(getpid());
    mx_printstr("\n");
    
    if(sid < 0)
    {
        return 1; 
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    return 0;
}

unsigned long mx_handle_post_file(char* req, char** filename) {
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jtype = json_object_object_get(jobj, "type");
    if(mx_strcmp(json_object_get_string(jtype), "POST-FILE")){
        return 0;
    }
    struct json_object *jfilename = json_object_object_get(jobj, "file_name");
    *filename = (char*)json_object_get_string(jfilename);
    struct json_object *jsize = json_object_object_get(jobj, "file_size");
    //mx_log_info(SYSLOG, (req));
    return json_object_get_uint64(jsize);
}

void* mx_create_server_client_session(void *server_ssl) {
    SSL *ssl = (SSL*)server_ssl;
    int hs_result;
    char buffer[MAXBUFFER];
    int file_flag = 0;
    char* filename = NULL;
    hs_result = mx_handshake(ssl, SERVER);
    unsigned long  filesize;
    if (hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            
            if(file_flag == 0){
                if(mx_SSL_read(ssl, buffer) == -1) break;
                //mx_log_info(SYSLOG, "vvv Get JSON from the client vvv");
                //mx_log_info(SYSLOG, buffer);
            }
            else {
                //mx_log_info(SYSLOG, "Start reading by parts");
                mx_SSL_readfile(ssl, mx_strjoin(RESPATH , filename), filesize);
                //mx_log_info(SYSLOG, "Stop reading by parts");
                file_flag = 0;
                ////mx_log_info(SYSLOG, mx_itoa(file_flag));
                // //mx_log_info(SYSLOG, mx_itoa(file_flag));
                continue;
            }  
            
            if(mx_strcmp(buffer, ":exit") == 0)
                break;
            
            if((filesize = mx_handle_post_file(buffer, &filename)) > 0) {
                file_flag = 1;
                ////mx_log_info(SYSLOG, mx_itoa(file_flag));
                continue;
            }
            
            main_handler(ssl, buffer);

        }
        
    }
    SSL_free(ssl);

    pthread_exit (0);
}