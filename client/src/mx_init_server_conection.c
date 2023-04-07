#include "client.h"

/* The function waits the server response and copy response to lbuffer of t_serv_connection object*/
void* mx_listen_server(void* data) {
    char buffer[MAXBUFFER];
    //mx_log_info("client.txt", "Listen -----\n");
    t_uchat_application* app = (t_uchat_application*)data;
    //mx_log_info("client.txt", mx_itoa(app->serv_connection->hs_result));

    if (app->serv_connection->hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            mx_SSL_read(app->serv_connection->ssl, buffer);
            if(buffer[0] != 0) {
                mx_strcpy(app->serv_connection->lbuffer, buffer);
                g_print("%s\n", buffer);
                main_handler(buffer);
            }
            // Add a hadnler for response
        }
    }
    return (void*)0;
}

/* The function for writing to server*/
void mx_write_to_server(SSL* ssl, char* buffer) {

    if(buffer != NULL && mx_strlen(buffer) < (int)(sizeof(char) * MAXBUFFER)){
        mx_SSL_write(ssl, buffer);
        mx_strdel(&buffer);
    }
 
}

void mx_init_server_connection(t_uchat_application* app, int port) {
    // char *ip    = IP;
    app->serv_connection = malloc(sizeof(t_serv_connection));
    app->serv_connection->port = port;   // TODO: validate port

    struct sockaddr_in client_addr = {0};
    app->serv_connection->socket = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    client_addr = mx_init_address(port, IP, AF_INET);

    app->serv_connection->ctx = mx_init_context(CLIENT);
    mx_use_certificate_key(app->serv_connection->ctx, CERTPATH, KEYPATH);

    app->serv_connection->ssl = mx_init_SSL_session(app->serv_connection->ctx, app->serv_connection->socket);
    mx_connect(app->serv_connection->socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
    app->serv_connection->hs_result = mx_handshake(app->serv_connection->ssl, CLIENT);

    pthread_create(&app->serv_connection->listener_thread, NULL, mx_listen_server, (void*)app); // Listening thread creation
}

