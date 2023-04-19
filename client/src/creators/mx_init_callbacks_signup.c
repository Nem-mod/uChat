#include "client.h"

void mx_init_callbacks_signup(t_uchat_application* app) {
    g_signal_connect(app->scenes->signup_scene->b_signup, "clicked", G_CALLBACK (mx_callback_registration), app);
    g_signal_connect(app->scenes->signup_scene->bl_signin, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->signup_scene->w_signup, "destroy", G_CALLBACK (mx_clear_app), app);
}
