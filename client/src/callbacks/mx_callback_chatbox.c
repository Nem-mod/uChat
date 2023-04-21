#include "client.h"

void mx_callback_chatbox(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application* app = (t_uchat_application*)data;
    struct json_object* jobj = json_object_new_object();

    GList *children = gtk_container_get_children(GTK_CONTAINER(button));
    children = gtk_container_get_children(GTK_CONTAINER(children->data));

    app->current_group_id = mx_atoi(gtk_widget_get_name(GTK_WIDGET(button)));
    app->last_message_indx = 0;
    app->last_message_id = 0;
    // TODO: don't destroy. create struct for each chat, hide/show messages. don't get them from server every time
    gtk_container_foreach(GTK_CONTAINER(app->scenes->chat_scene->l_sc_messages), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *chat_image = children->data;
    children = g_list_next(children);
    GtkLabel *chat_label = GTK_LABEL(children->data);
    

    // mx_log_info(SYSLOG, "current_group_id = vvv");
    // mx_log_info(SYSLOG, (char*)gtk_widget_get_name(GTK_WIDGET(button)));

    // mx_log_info(SYSLOG, "button label = vvv");
    // mx_log_info(SYSLOG, (char*)gtk_label_get_text(chat_label));
    gtk_label_set_text(GTK_LABEL(app->scenes->chat_scene->l_chatname), gtk_label_get_text(chat_label));

    mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->img_chat), chat_image, gtk_widget_get_name(chat_image));
    // gtk_image_set_from_file(GTK_IMAGE(app->scenes->chat_scene->img_chat), gtk_widget_get_name(chat_image));

    json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));
    mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/group/message", jobj));
}
