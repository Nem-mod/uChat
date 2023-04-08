#include "client.h"

void mx_init_scene_signin(GtkBuilder *builder, t_uchat_application* app) {
    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->signin_scene = malloc(sizeof(t_signin_scene));

    *new_scene = SIGNUP;
    app->scenes->signin_scene->cbdata = mx_create_callback_data(app, new_scene);

    app->scenes->signin_scene->w_signin = mx_get_widget(builder, "signin_window");
    app->scenes->signin_scene->e_f_login = mx_get_widget(builder, "login_entry1");
    app->scenes->signin_scene->e_f_password = mx_get_widget(builder, "password_entry1");
    app->scenes->signin_scene->b_signin = mx_get_widget(builder, "signin_button");
    app->scenes->signin_scene->bl_signup = mx_get_widget(builder, "signin_link1");

    g_signal_connect(app->scenes->signin_scene->b_signin, "clicked", G_CALLBACK (mx_callback_auth), app);
    g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->signin_scene->w_signin, "destroy", G_CALLBACK (mx_clear_app), app);

    gtk_widget_hide(app->scenes->signin_scene->w_signin);
}
