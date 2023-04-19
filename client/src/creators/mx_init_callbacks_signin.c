#include "client.h"

void mx_init_callbacks_signin(t_uchat_application* app) {
    g_signal_connect(app->scenes->signin_scene->b_signin, "clicked", G_CALLBACK (mx_callback_auth), app);
    g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signup_scene->cbdata);
    g_signal_connect(app->scenes->signin_scene->w_signin, "destroy", G_CALLBACK (mx_clear_app), app);
}
