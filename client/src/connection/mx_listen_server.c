#include "client.h"

void* mx_listen_server(void* data) {
    char buffer[MAXBUFFER];
    t_uchat_application* app = (t_uchat_application*)data;
    int file_flag = 0;
    char* filename = NULL;
    unsigned long  filesize;
    if (app->serv_connection->hs_result != 0) {
        mx_log_info(SYSLOG, "Handshake is done");

        while (1) {
            if(file_flag == 0){
                if(mx_SSL_read(app->serv_connection->ssl, buffer) == -1) break;
            }
            else {
                mx_SSL_readfile(app->serv_connection->ssl, mx_strjoin(RESOURCE_PATH , filename), filesize);
                file_flag = 0;

                continue;
            }  
            
            if((filesize = mx_handle_post_file(buffer, &filename)) > 0) {
                file_flag = 1;
                continue;
            }
            

            if(buffer[0] != 0) {
                mx_log_info(SYSLOG, "vvv Get JSON from the server vvv");
                mx_log_info(SYSLOG, buffer);

                mx_strcpy(app->serv_connection->lbuffer, buffer);
                mx_main_handler(buffer, app);
            }
            mx_memset(&buffer, 0, sizeof(buffer));
        }
    } else
        mx_log_err(SYSLOG, "Handshake error");
    mx_log_info(SYSLOG, "Exit the listener");

    return NULL;
}
