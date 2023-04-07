#include "client.h"

t_uchat_application* mx_create_app(char* argv[]) {
    t_uchat_application* app = malloc(sizeof(t_uchat_application));

    mx_create_scenes(app);
    mx_init_server_connection(app, mx_atoi(argv[1]));

    return app;
}



