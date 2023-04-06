#include "client.h"

/* The function waits the server response and copy response to lbuffer of t_serv_connection object*/
void* mx_listen_server(void* data) {
    char buffer[MAXBUFFER];
    //mx_log_info("client.txt", "Listen -----\n");
    t_serv_connection* s_con = (t_serv_connection*)data;
    //mx_log_info("client.txt", mx_itoa(s_con->hs_result));

    if (s_con->hs_result != 0) {
        while (1) {
            mx_memset(&buffer, 0, sizeof(buffer));
            mx_SSL_read(s_con->ssl, buffer);
            if(buffer[0] != 0) {
                mx_strcpy(s_con->lbuffer, buffer);
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

t_serv_connection *mx_init_server_conection(int port){
    char *ip    = IP;
    t_serv_connection* serv_connection = malloc(sizeof(t_serv_connection));
    serv_connection->port = port;

    struct sockaddr_in client_addr = {0};
    serv_connection->socket = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    client_addr = mx_init_address(port, ip, AF_INET);

    serv_connection->ctx = mx_init_context(CLIENT);
    mx_use_certificate_key(serv_connection->ctx, CERTPATH, KEYPATH);

    serv_connection->ssl = mx_init_SSL_session(serv_connection->ctx, serv_connection->socket);
    mx_connect(serv_connection->socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
    serv_connection->hs_result = mx_handshake(serv_connection->ssl, CLIENT);

    pthread_create(&serv_connection->listener_thread, NULL, mx_listen_server, (void*)serv_connection); // Listening thread creation

    return serv_connection;
}

