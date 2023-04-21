#include "client.h"

void mx_init_scene_signin(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    const gchar *path = "client/Resources/css/signin.css";
    // const gchar *path = "client/Resources/css/gtk.css";
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_SIGNIN_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->signin_scene = malloc(sizeof(t_signin_scene));

    *new_scene = SIGNIN;
    app->scenes->signin_scene->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->signin_scene->w_signin = mx_get_widget(builder, "signin_window");
    //app->scenes->signin_scene->gr_signin = mx_get_widget(builder, "login_grid");
    app->scenes->signin_scene->e_f_login = mx_get_widget(builder, "login_entry1");
    app->scenes->signin_scene->e_f_password = mx_get_widget(builder, "password_entry1");
    app->scenes->signin_scene->b_signin = mx_get_widget(builder, "signin_button");
    app->scenes->signin_scene->bl_signup = mx_get_widget(builder, "signin_link1");
    app->scenes->signin_scene->l_err_msg = mx_get_widget(builder, "err_msg");
    //gtk_widget_set_visible(app->scenes->signin_scene->gr_signin, TRUE);

    mx_set_style(path, app->scenes->signin_scene->e_f_login);
    mx_set_style(path, app->scenes->signin_scene->e_f_password);
    mx_set_style(path, app->scenes->signin_scene->b_signin);
    mx_set_style(path, app->scenes->signin_scene->l_err_msg);
    mx_set_style(path, app->scenes->signin_scene->bl_signup);
    mx_set_style(path, app->scenes->signin_scene->w_signin);

    
    gtk_widget_hide(app->scenes->signin_scene->w_signin);
    g_object_unref(builder);
}
