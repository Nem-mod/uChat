#include "client.h"


void mx_init_signup(GtkBuilder *builder, t_UchatApplication* app) {
    app->scenes->signUp_scene = malloc(sizeof(t_signupScene));
    app->scenes->signUp_scene->w_signup = mx_get_widget(builder, "signup_window");
    app->scenes->signUp_scene->e_f_login = mx_get_widget(builder, "login_entry");
    app->scenes->signUp_scene->e_f_password = mx_get_widget(builder, "password_entry");
    app->scenes->signUp_scene->e_f_password2 = mx_get_widget(builder, "r_password_entry");
    app->scenes->signUp_scene->e_f_firstName = mx_get_widget(builder, "fname_entry");
    app->scenes->signUp_scene->e_f_lastName = mx_get_widget(builder, "lname_entry");
    app->scenes->signUp_scene->b_signup = mx_get_widget(builder, "register_button");
    app->scenes->signUp_scene->bl_signin = mx_get_widget(builder, "signin_link");

    g_signal_connect (app->scenes->signUp_scene->b_signup, "clicked", G_CALLBACK (mx_registratinon_callback), app);
    g_signal_connect (app->scenes->signUp_scene->w_signup, "destroy", G_CALLBACK (mx_clear_app), app);
}

void mx_create_scenes(t_UchatApplication* app) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, "client/Resources/gui/builder.ui", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    app->scenes = malloc(sizeof(t_uchatScenes));
    mx_init_signup(builder, app);
}
