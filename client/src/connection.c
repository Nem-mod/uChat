#include "client.h"

void mx_init_server_connection(t_uchat_application* app, int port) {
    struct sockaddr_in client_addr = {0};

    if(app->serv_connection != NULL)
        app->serv_connection = NULL;
    
    app->serv_connection = malloc(sizeof(t_serv_connection));
    
    app->serv_connection->port = port;  // TODO: validate port
    app->serv_connection->socket = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    client_addr = mx_init_address(port, IP, AF_INET);

    app->serv_connection->ctx = mx_init_context(CLIENT);
    mx_use_certificate_key(app->serv_connection->ctx, CERTPATH, KEYPATH);

    app->serv_connection->ssl = mx_init_SSL_session(app->serv_connection->ctx, app->serv_connection->socket);
    while (1) {
        if(mx_connect(app->serv_connection->socket, (struct sockaddr*)&client_addr, sizeof(client_addr)) != -1)
            break;
    }
    
    app->serv_connection->hs_result = mx_handshake(app->serv_connection->ssl, CLIENT);

    pthread_create(&app->serv_connection->listener_thread, NULL, mx_listen_server, (void*)app); // Listening thread creation
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

void* mx_listen_server(void* data) {
    char buffer[MAXBUFFER];
    t_uchat_application* app = (t_uchat_application*)data;
    int file_flag = 0;
    char* filename = NULL;
    unsigned long  filesize;
    if (app->serv_connection->hs_result != 0) {
        //mx_log_info(SYSLOG, "Handshake is done");

        while (1) {
            if(file_flag == 0){
                if(mx_SSL_read(app->serv_connection->ssl, buffer) == -1) break;
                // //mx_log_info(SYSLOG, buffer);
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
                //mx_log_info(SYSLOG, "vvv Get JSON from the server vvv");
                //mx_log_info(SYSLOG, buffer);

                mx_strcpy(app->serv_connection->lbuffer, buffer);
                mx_main_handler(buffer, app);
            }
            mx_memset(&buffer, 0, sizeof(buffer));
        }
    } else
        //mx_log_err(SYSLOG, "Handshake error");
    //mx_log_info(SYSLOG, "Exit the listener");

    mx_init_server_connection(app, app->serv_connection->port);
    return NULL;
}

void mx_write_to_server(SSL* ssl, char* buffer) {

    if(buffer != NULL && mx_strlen(buffer) < (int)(sizeof(char) * MAXBUFFER)){
        //mx_log_info(SYSLOG, "vvv Pass JSON to the server vvv");
        //mx_log_info(SYSLOG, buffer);

        mx_SSL_write(ssl, buffer);
        mx_strdel(&buffer);
    } else
        mx_log_err(SYSLOG, "Write failed");
 
}
