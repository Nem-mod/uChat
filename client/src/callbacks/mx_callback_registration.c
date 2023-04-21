#include "client.h"

void mx_callback_registration(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    bool err = false;

    int login_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_login)); 
    if (login_len < 3) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_login_err), "Login must contain more than 2 characters");
        err = true;
    } 
    else if (login_len > 32) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_login_err), "Login can be up to 32 characters");
        err = true;
    } 
    else {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_login_err), "");
    }
    const char *login = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_login)));

    int pass_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_password)); 
    if (pass_len < 8) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "Invalid password (< 8)");
        err = true;
    }
    else if (pass_len > 18) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "Invalid password (> 18)");
        err = true;
    }
    else if (mx_validate_password_digits((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_password))) != 0) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "Invalid password (must contain digits)");
        err = true;
    }
    else if (mx_validate_password_letters((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_password))) != 0) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "Invalid password (must contain letters)");
        err = true;
    }
    else {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "");        
    }
    const char *password = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_password)));
    const char *password2 = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_password2)));

    int fname_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_firstName)); 
    if (fname_len < 3) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_first_name_err), "Invalid first name (< 3)");
        err = true;
    }
    else if (fname_len > 64) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_first_name_err), "Invalid first name (> 64)");
        err = true;
    }
    else {  
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_first_name_err), "");
    }
    const char *first_name = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_firstName)));

    int lname_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->signup_scene->e_f_lastName)); 
    if (lname_len < 3) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_second_name_err), "Invalid last name (< 3)");
        err = true;
    }
    else if (lname_len > 64) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_second_name_err), "Invalid last name (> 64)");
        err = true;
    }
    else {  
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_second_name_err), "");
    }
    const char *last_name = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->signup_scene->e_f_lastName)));
 
    if(mx_strcmp(password, password2) != 0) {
        /*
            Add handle password
            if password != password2 
            change gui, print err
        */
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_repeat_password_err), "Passwords must match");
        err = true;
    }
    else {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_repeat_password_err), "");
    }

    if (err) {
        return;
    }
    else {
        gtk_label_set_text(GTK_LABEL(app->scenes->signin_scene->l_err_msg), "");
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "");   
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_first_name_err), "");
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_second_name_err), "");
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_repeat_password_err), "");
        
        mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_login));
        mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_password));
        mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_password2));
        mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_firstName));
        mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_lastName));
    }

    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "login", json_object_new_string(login));
    json_object_object_add(jobj, "password", json_object_new_string(password2));
    json_object_object_add(jobj, "first_name", json_object_new_string(first_name));
    json_object_object_add(jobj, "last_name", json_object_new_string(last_name));

    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("POST","/auth/register", jobj));
}
