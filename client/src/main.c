#include "client.h"

int main(int argc, char* argv[])
{
    remove(SYSLOG);
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat [port]");
        return 0;
    }

    t_serv_connection* serv = mx_init_server_conection(mx_atoi(argv[1]));
    mx_printint(serv->port);
    // pthread_t thread_id;
      
    // pthread_create(&thread_id, NULL, mx_init_server_conection, (void*)ssl);
    // close(client_sock);
    // SSL_CTX_free(ctx);  
    char buffer[MAXBUFFER];
    char *json = "{ \"type\": \"POST\", \
        \"url\": \"/auth/register\", \
        \"property\": { \"login\": \"nemmmmmmmdadmm\", \
            \"password\": \"1223\", \
            \"first_name\": \"1223\", \
            \"last_name\": \"1223\" \
        }" \
    "}";
    if (serv->hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            
            mx_printstr("Client: ");
            mx_strcpy(buffer, json);
            mx_printstr("\n");
            char temp[245];
            scanf("%s", temp);
            
            mx_SSL_write(serv->ssl, buffer);

            

            mx_memset(&buffer, 0, sizeof(buffer));
            mx_SSL_read(serv->ssl, buffer);

            mx_printstr("Server: ");
            mx_printstr(buffer);
            mx_printstr("\n");
        }
    }
    mx_printstr("Disconnected from the server.\n");

    return 0;
}
