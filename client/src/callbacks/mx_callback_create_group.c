#include "client.h"

void mx_callback_create_group(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    
    int login_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->create_group_dwindow->e_f_group_name)); 
    if(login_len < 3 || login_len > 32) {return;}
    const char *login = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->create_group_dwindow->e_f_group_name));


    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
    json_object_object_add(jobj, "group_name", json_object_new_string((char*)login));
    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("POST","/group/", jobj));
    mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/user/groups", jobj));
    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
}
