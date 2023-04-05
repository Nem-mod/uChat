#include "client.h"

t_UchatApplication* mx_create_app(char* argv[]) {
    t_UchatApplication* app = malloc(sizeof(t_UchatApplication));
    app->serv_conection = mx_init_server_conection(mx_atoi(argv[1]));
    app->scenes = mx_create_scenes();
    return app;
}



