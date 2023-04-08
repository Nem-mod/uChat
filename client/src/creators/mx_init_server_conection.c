#include "client.h"

void mx_init_server_connection(t_uchat_application* app, int port) {
    struct sockaddr_in client_addr = {0};
    app->serv_connection = malloc(sizeof(t_serv_connection));
    
    app->serv_connection->port = port;  // TODO: validate port
    app->serv_connection->socket = mx_create_socket(AF_INET, SOCK_STREAM, 0);
    client_addr = mx_init_address(port, IP, AF_INET);

    app->serv_connection->ctx = mx_init_context(CLIENT);
    mx_use_certificate_key(app->serv_connection->ctx, CERTPATH, KEYPATH);

    app->serv_connection->ssl = mx_init_SSL_session(app->serv_connection->ctx, app->serv_connection->socket);
    mx_connect(app->serv_connection->socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
    app->serv_connection->hs_result = mx_handshake(app->serv_connection->ssl, CLIENT);

    pthread_create(&app->serv_connection->listener_thread, NULL, mx_listen_server, (void*)app); // Listening thread creation
}

