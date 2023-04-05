#include "client.h"


void mx_registratinon_callback(GtkButton *button, gpointer data) {
    t_UchatApplication *app = (t_UchatApplication*)data;
    const char *login = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signUp_scene->e_f_login));
    const char *password = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signUp_scene->e_f_password));
    const char *password2 = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signUp_scene->e_f_password2));
    const char *first_name = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signUp_scene->e_f_firstName));
    const char *last_name = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signUp_scene->e_f_lastName));

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

