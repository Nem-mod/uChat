#include "client.h"

void mx_init_scene_signup(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;
    const gchar *path = "client/Resources/css/signup.css";


    if (gtk_builder_add_from_file(builder, RESOURCE_SIGNUP_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->signup_scene = malloc(sizeof(t_signup_scene));

    *new_scene = SIGNUP;
    app->scenes->signup_scene->cbdata = mx_create_callback_data(app, new_scene);

    app->scenes->signup_scene->w_signup = mx_get_widget(builder, "signup_window");
    app->scenes->signup_scene->e_f_login = mx_get_widget(builder, "login_entry");
    app->scenes->signup_scene->e_f_password = mx_get_widget(builder, "password_entry");
    app->scenes->signup_scene->e_f_password2 = mx_get_widget(builder, "r_password_entry");
    app->scenes->signup_scene->e_f_firstName = mx_get_widget(builder, "fname_entry");
    app->scenes->signup_scene->e_f_lastName = mx_get_widget(builder, "lname_entry");
    app->scenes->signup_scene->b_signup = mx_get_widget(builder, "register_button");
    app->scenes->signup_scene->bl_signin = mx_get_widget(builder, "signin_link");

    app->scenes->signup_scene->l_first_name_err = mx_get_widget(builder, "first_name_err");
    app->scenes->signup_scene->l_second_name_err = mx_get_widget(builder, "last_name_err");
    app->scenes->signup_scene->l_login_err = mx_get_widget(builder, "login_err");
    app->scenes->signup_scene->l_password_err = mx_get_widget(builder, "password_err");
    app->scenes->signup_scene->l_repeat_password_err = mx_get_widget(builder, "repeat_password_err");

    mx_set_style(path, app->scenes->signup_scene->w_signup);
    mx_set_style(path, app->scenes->signup_scene->e_f_login);
    mx_set_style(path, app->scenes->signup_scene->e_f_password);
    mx_set_style(path, app->scenes->signup_scene->e_f_password2);
    mx_set_style(path, app->scenes->signup_scene->e_f_firstName);
    mx_set_style(path, app->scenes->signup_scene->e_f_lastName);
    mx_set_style(path, app->scenes->signup_scene->b_signup);

    mx_set_style(path, app->scenes->signup_scene->l_first_name_err);
    mx_set_style(path, app->scenes->signup_scene->l_second_name_err);
    mx_set_style(path, app->scenes->signup_scene->l_login_err);
    mx_set_style(path, app->scenes->signup_scene->l_password_err);
    mx_set_style(path, app->scenes->signup_scene->l_repeat_password_err);

    gtk_widget_hide(app->scenes->signup_scene->w_signup);
    g_object_unref(builder);
}
