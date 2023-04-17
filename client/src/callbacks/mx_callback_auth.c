#include "client.h"

#include "client.h"


void mx_callback_auth(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    
    // int login_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_login)); 
    // if(login_len < 3 || login_len > 32) {return;}
    const char *login = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signin_scene->e_f_login));

    // int pass_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_password)); 
    // if(pass_len < 8 || pass_len > 18) {return;}
    const char *password = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signin_scene->e_f_password));

   
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "login", json_object_new_string(login));
    json_object_object_add(jobj, "password", json_object_new_string(password));
    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/auth/me", jobj));
}
