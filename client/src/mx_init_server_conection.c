#include "client.h"


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
    return serv_connection;
}

