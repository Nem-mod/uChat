#include "client.h"

void mx_init_scene_create_group(t_uchat_application* app) {
    if(app){}
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CREATE_GROUP_PATH, &error) == 0) {
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->create_group_dwindow = malloc(sizeof(t_create_group));

    *new_scene = CREATE_GROUP;
    app->scenes->create_group_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->create_group_dwindow->w_create_group = mx_get_widget(builder, "create_group_window");
    app->scenes->create_group_dwindow->e_f_group_name = mx_get_widget(builder, "group_name_entry_contact");
    app->scenes->create_group_dwindow->b_create_group = mx_get_widget(builder, "add_group_button");
    app->scenes->create_group_dwindow->b_close = mx_get_widget(builder, "cancel_button");
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->create_group_dwindow->w_create_group), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
}
