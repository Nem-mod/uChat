#include "client.h"


void mx_callback_add_contact(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    
    int login_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->add_contact_dwindow->e_f_login)); 
    if(login_len < 3 || login_len > 32) {return;}
    const char *login = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->add_contact_dwindow->e_f_login));

    // int pass_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_password)); 
    // if(pass_len < 8 || pass_len > 18) {return;}

   
    // struct json_object *jobj = json_object_new_object();
    // json_object_object_add(jobj, "user_id", json_object_new_int(app->user->id));
    // json_object_object_add(jobj, "login", json_object_new_string(login));
    // mx_write_to_server(app->serv_connection->ssl,  mx_create_request("POST","/contact/", jobj));


    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
    json_object_object_add(jobj, "login", json_object_new_string((char*)login));
    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("POST","/contact/", jobj));
    mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/user/groups", jobj));
    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
}
