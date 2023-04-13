#include "client.h"

void* mx_listen_server(void* data) {
    char buffer[MAXBUFFER];
    t_uchat_application* app = (t_uchat_application*)data;

    if (app->serv_connection->hs_result != 0) {
        mx_log_info(SYSLOG, "Handshake is done");

        while (1) {
            mx_log_info(SYSLOG, "Ready to listen");
            
            mx_memset(&buffer, 0, sizeof(buffer));
            if(mx_SSL_read(app->serv_connection->ssl, buffer) == -1) break;;
            if(buffer[0] != 0) {
                mx_log_info(SYSLOG, "vvv Get JSON from the server vvv");
                mx_log_info(SYSLOG, buffer);

                mx_strcpy(app->serv_connection->lbuffer, buffer);
                mx_main_handler(buffer, app);
            }
        }
    } else
        mx_log_err(SYSLOG, "Handshake error");
    mx_log_info(SYSLOG, "Exit the listener");

    return NULL;
}
