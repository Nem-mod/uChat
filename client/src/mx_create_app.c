#include "client.h"

t_UchatApplication* mx_create_app(char* argv[]) {
    t_UchatApplication* app = malloc(sizeof(t_UchatApplication));
    app->serv_conection = mx_init_server_conection(mx_atoi(argv[1]));
    app->scenes = mx_create_scenes();

    g_signal_connect (app->scenes->signUp_scene->b_signup, "clicked", G_CALLBACK (mx_registratinon_callback), app);
    g_signal_connect (app->scenes->signUp_scene->w_signup, "destroy", G_CALLBACK (mx_clear_app), app);

    return app;
}



