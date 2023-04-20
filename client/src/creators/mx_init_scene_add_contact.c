#include "client.h"

void mx_init_scene_add_contact(t_uchat_application* app) {
    if(app){}
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    const gchar *path = "client/Resources/css/addcontact.css";
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_ADD_CONT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->add_contact_dwindow = malloc(sizeof(t_signin_scene));

    *new_scene = ADD_CONTACT;
    app->scenes->add_contact_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->add_contact_dwindow->w_add_contact= mx_get_widget(builder, "addcontact_window");
    //app->scenes->signin_scene->gr_signin = mx_get_widget(builder, "login_grid");
    app->scenes->add_contact_dwindow->e_f_login = mx_get_widget(builder, "login_entry_contact");
    app->scenes->add_contact_dwindow->b_add_contact = mx_get_widget(builder, "add_contact_button");
    app->scenes->add_contact_dwindow->b_close = mx_get_widget(builder, "cancel_button");

    mx_set_style(path, app->scenes->add_contact_dwindow->e_f_login);
    mx_set_style(path, app->scenes->add_contact_dwindow->b_add_contact);
    mx_set_style(path, app->scenes->add_contact_dwindow->b_close);

    //gtk_widget_set_visible(app->scenes->signin_scene->gr_signin, TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->add_contact_dwindow->w_add_contact), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
}
