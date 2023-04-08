#include "client.h"

void mx_init_scene_signup(GtkBuilder *builder, t_uchat_application* app) {
    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->signup_scene = malloc(sizeof(t_signup_scene));

    *new_scene = SIGNIN;
    app->scenes->signup_scene->cbdata = mx_create_callback_data(app, new_scene);

    app->scenes->signup_scene->w_signup = mx_get_widget(builder, "signup_window");
    app->scenes->signup_scene->e_f_login = mx_get_widget(builder, "login_entry");
    app->scenes->signup_scene->e_f_password = mx_get_widget(builder, "password_entry");
    app->scenes->signup_scene->e_f_password2 = mx_get_widget(builder, "r_password_entry");
    app->scenes->signup_scene->e_f_firstName = mx_get_widget(builder, "fname_entry");
    app->scenes->signup_scene->e_f_lastName = mx_get_widget(builder, "lname_entry");
    app->scenes->signup_scene->b_signup = mx_get_widget(builder, "register_button");
    app->scenes->signup_scene->bl_signin = mx_get_widget(builder, "signin_link");

    g_signal_connect(app->scenes->signup_scene->b_signup, "clicked", G_CALLBACK (mx_callback_registration), app);
    g_signal_connect(app->scenes->signup_scene->bl_signin, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signup_scene->cbdata);
    g_signal_connect(app->scenes->signup_scene->w_signup, "destroy", G_CALLBACK (mx_clear_app), app);

    gtk_widget_hide(app->scenes->signup_scene->w_signup);
}
