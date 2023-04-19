#include "client.h"

void mx_callback_chatbox(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application* app = (t_uchat_application*)data;
    //g_print("%s",  gtk_widget_get_name(GTK_WIDGET( button)));
    app->current_group_id = mx_atoi(gtk_widget_get_name(GTK_WIDGET(button)));
    struct json_object* jobj = json_object_new_object();
  //  json_object_object_add(jobj, "group_id", json_object_new_string(gtk_widget_get_name(GTK_WIDGET( button))));
    mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/group/message", jobj));
    
}
