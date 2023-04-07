#include "client.h"


void mx_registratinon_callback(GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    int login_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_login)); 
    if(login_len < 3 || login_len > 32) {return;}
    const char *login = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_login));


    int pass_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_password)); 
    if(pass_len < 8 || pass_len > 18) {return;}
    const char *password = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_password));
    const char *password2 = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_password2));

    int fname_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_firstName)); 
    if(fname_len < 3 || fname_len > 64) {return;}
    const char *first_name = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_firstName));

    int lname_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_lastName)); 
    if(lname_len < 3 || lname_len > 64) {return;}
    const char *last_name = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_lastName));
 

    if(mx_strcmp(password, password2) != 0) {
        /*
            Add handle password
            if password != password2 
            change gui, print err
        */
       return;
    }

    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "login", json_object_new_string(login));
    json_object_object_add(jobj, "password", json_object_new_string(password2));
    json_object_object_add(jobj, "first_name", json_object_new_string(first_name));
    json_object_object_add(jobj, "last_name", json_object_new_string(last_name));
    mx_write_to_server(app->serv_conection->ssl,  mx_create_str_jreq("POST","/auth/register", jobj));
    (void)button;
}

