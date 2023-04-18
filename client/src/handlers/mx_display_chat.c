#include "client.h"

void mx_display_chat(t_uchat_application* app, t_response* res) {
    if(res){}
    

    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    GtkWidget *chat_box = mx_get_widget(builder, "chat_box");
    // GtkWidget *chat_img = mx_get_widget(builder, "chat_img");
    // GtkWidget *chat_name = mx_get_widget(builder, "chat_name");
    gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats), chat_box, -1);
    g_object_unref(builder);
}

