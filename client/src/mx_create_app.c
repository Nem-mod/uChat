#include "client.h"

t_uchat_application* mx_create_app(char* argv[]) {
    t_uchat_application* app = malloc(sizeof(t_uchat_application));
    app->serv_conection = mx_init_server_conection(mx_atoi(argv[1]));
    mx_create_scenes(app);

    return app;
}



