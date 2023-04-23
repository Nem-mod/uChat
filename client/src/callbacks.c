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

    gtk_entry_set_text(GTK_ENTRY(app->scenes->add_contact_dwindow->e_f_login), "");
    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
}

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

void mx_callback_change_scene(UNUSED GtkButton *button, gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_change_scenes(cbdata->app, *(t_SCENE*)cbdata->data);
}

void mx_callback_chatbox(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application* app = (t_uchat_application*)data;
    struct json_object* jobj = json_object_new_object();

    GList *children = gtk_container_get_children(GTK_CONTAINER(button));
    
    if(mx_atoi((char*)gtk_widget_get_name((GTK_WIDGET(children->data)))) != 0)
        gtk_widget_hide(app->scenes->chat_scene->b_chat_settings);
    else    
        gtk_widget_show(app->scenes->chat_scene->b_chat_settings);

    children = gtk_container_get_children(GTK_CONTAINER(children->data));
   
    app->current_group_id = mx_atoi(gtk_widget_get_name(GTK_WIDGET(button)));
    app->last_message_indx = 0;
    app->last_message_id = 0;
    // TODO: don't destroy. create struct for each chat, hide/show messages. don't get them from server every time
    gtk_container_foreach(GTK_CONTAINER(app->scenes->chat_scene->l_sc_messages), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *chat_image = children->data;
    children = g_list_next(children);
    GtkLabel *chat_label = GTK_LABEL(children->data);
    
    gtk_label_set_text(GTK_LABEL(app->scenes->chat_scene->l_chatname), gtk_label_get_text(chat_label));

    mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->img_chat), chat_image, gtk_widget_get_name(chat_image));
    gtk_widget_set_name(app->scenes->chat_scene->img_chat, gtk_widget_get_name(chat_image));
    mx_log_err(SYSLOG, (char*)gtk_widget_get_name(app->scenes->chat_scene->img_chat)); // TODO: temp
    // gtk_image_set_from_file(GTK_IMAGE(app->scenes->chat_scene->img_chat), gtk_widget_get_name(chat_image));

    json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));
    mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/group/message", jobj));
}

void mx_callback_choose_file(GtkFileChooserButton *button, gpointer data) {
    t_uchat_application* app = (t_uchat_application*)data;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button);
    GtkFileChooserAction action = gtk_file_chooser_get_action(chooser);
    if(app->choosed_file_pname != NULL) {
            mx_strdel(&app->choosed_file_pname);
    }
    if (action == GTK_FILE_CHOOSER_ACTION_OPEN) {
        
        gchar *filename = gtk_file_chooser_get_filename(chooser);
        app->choosed_file_pname = mx_strdup((char*)filename);
        g_free(filename);
    }
    //g_print("Selected file %s\n", app->choosed_file_pname);
}

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

void mx_callback_hide_window(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data; 

    gtk_entry_set_text(GTK_ENTRY(app->scenes->add_contact_dwindow->e_f_login), "");
    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
    app->active_scene = CHAT;
}

void mx_callback_hide_window_crt(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data; 

    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
    app->active_scene = CHAT;
}

void mx_callback_hide_window_group_info(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data; 

    gtk_widget_hide(app->scenes->group_info_dwindow->w_group_info);
    app->active_scene = CHAT;
}

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

void mx_callback_select_chat(UNUSED GtkButton *button, UNUSED gpointer data) { // TODO:: delete this
    g_print("Hello motherfuckers\n");
}

void mx_callback_send_message(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    if(app->current_group_id == 0) 
        return;
    
    int message_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->chat_scene->e_f_chat)); 
    if(message_len <= 0 || message_len > 256) {return;}
    char *message_text_entry = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->chat_scene->e_f_chat));
    
  
    struct json_object *jobj = json_object_new_object();

    

    json_object_object_add(jobj, "message_text", json_object_new_string(message_text_entry));
    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
    json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));
    json_object_object_add(jobj, "sent_datatime", json_object_new_string(mx_get_formatted_time()));

    if(app->choosed_file_pname) {
        unsigned int file_size = get_file_size(app->choosed_file_pname);
        if(file_size > 0) {
            char filename[50];
            char *pos = strrchr(app->choosed_file_pname, '/');
            strcpy(filename, pos + 1);
            struct json_object *jfobj = json_object_new_object();
            json_object_object_add(jfobj, "file_name", json_object_new_string(filename));
            json_object_object_add(jfobj, "file_size", json_object_new_uint64(file_size));
            json_object_object_add(jfobj, "type", json_object_new_string("POST-FILE"));
            mx_write_to_server(app->serv_connection->ssl,  (char*)json_object_to_json_string(jfobj));
            mx_SSL_sendfile(app->serv_connection->ssl, app->choosed_file_pname, file_size);
            json_object_object_add(jobj, "file_name", json_object_new_string(filename));
            json_object_object_add(jobj, "file_size", json_object_new_uint64(file_size));
        }
    }
    
    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("POST","/group/message", jobj));

    mx_clear_entry(GTK_ENTRY(app->scenes->chat_scene->e_f_chat));

    if (app->choosed_file_pname) {
        // gtk_file_chooser_unselect_filename(GTK_FILE_CHOOSER(app->scenes->chat_scene->e_f_file), app->choosed_file_pname);
        // gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(app->scenes->chat_scene->e_f_file));
        // gtk_file_chooser_button_set_title(GTK_FILE_CHOOSER_BUTTON(app->scenes->chat_scene->e_f_file), "Cock");
        
        // gtk_file_chooser_remove_choice(  FIXME: fix
        //     app->scenes->chat_scene->e_f_file, 
        //     gtk_file_chooser_get_choice(app->scenes->chat_scene->e_f_file)
        // );
    }
    // gtk_file_chooser_button_set_title(app->scenes->chat_scene->e_f_file, "");
    
    if(app->choosed_file_pname != NULL) {
            mx_strdel(&app->choosed_file_pname);
    }
    //mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/message", jobj));
}

void mx_callback_test(UNUSED GtkButton *button, UNUSED gpointer data) { // TODO:: delete this
    mx_log_info(SYSLOG, "CALLBACK TEST is called!");
}

void mx_callback_log_out(UNUSED GtkButton *button, UNUSED gpointer data) { // TODO:: delete this
    t_uchat_application *app = (t_uchat_application*)data;
    app->choosed_file_pname = NULL;
    app->current_group_id = 0;
    app->last_message_id = 0;
    app->last_message_indx = 0;
    app->user_id = 0;
    app->active_scene = SIGNIN;
    gtk_container_foreach(GTK_CONTAINER(app->scenes->chat_scene->l_sc_chats), (GtkCallback)gtk_widget_destroy, NULL);
    gtk_container_foreach(GTK_CONTAINER(app->scenes->chat_scene->l_sc_messages), (GtkCallback)gtk_widget_destroy, NULL);
    gdk_threads_add_idle(mx_handler_change_scene, app->scenes->signin_scene->cbdata);
    gtk_widget_hide(app->scenes->user_profile_dwindow->w_user_profile);
    gtk_widget_hide(app->scenes->chat_scene->w_chat);
   
}

gboolean mx_callback_on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    GtkWidget *window = (GtkWidget*)data; 
    if(event || widget){} 
    gtk_widget_hide(window);
    return TRUE;
}

void mx_callback_patch_user(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
    

    if(app->choosed_file_pname) {
        unsigned int file_size = get_file_size(app->choosed_file_pname);
        if(file_size > 0) {
            char filename[50];
            char *pos = strrchr(app->choosed_file_pname, '/');
            strcpy(filename, pos + 1);
            struct json_object *jfobj = json_object_new_object();
            json_object_object_add(jfobj, "file_name", json_object_new_string(filename));
            json_object_object_add(jfobj, "file_size", json_object_new_uint64(file_size));
            json_object_object_add(jfobj, "type", json_object_new_string("POST-FILE"));
            mx_write_to_server(app->serv_connection->ssl,  (char*)json_object_to_json_string(jfobj));
            mx_SSL_sendfile(app->serv_connection->ssl, app->choosed_file_pname, file_size);
            json_object_object_add(jobj, "file_name", json_object_new_string(filename));
            json_object_object_add(jobj, "file_size", json_object_new_uint64(file_size));
        }
        mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->img_user), 
                                (app->scenes->chat_scene->img_user),  
                                app->choosed_file_pname);

        if(app->choosed_file_pname != NULL) {
                mx_strdel(&app->choosed_file_pname);
        }
    }
    
    
    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("PATCH","/user/", jobj));
    
}

void mx_callback_set_up_profile_image(UNUSED GtkButton *button, UNUSED gpointer data) { 
    t_uchat_application *app = (t_uchat_application*)data;
    mx_set_image_widget_size(GTK_IMAGE(app->scenes->user_profile_dwindow->img_user), 
                                        (app->scenes->user_profile_dwindow->img_user),  
                                        app->choosed_file_pname);
}

void mx_callback_search_by_chats(UNUSED GtkButton *button, gpointer data){
    t_uchat_application* app = (t_uchat_application*)data;
    const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(app->scenes->chat_scene->e_f_chats));

    

    GtkListBox *listbox = GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats);

    GList *rows = gtk_container_get_children(GTK_CONTAINER(listbox));

    for (GList *iter = rows; iter != NULL; iter = iter->next) {
        GtkListBoxRow *row = GTK_LIST_BOX_ROW(iter->data);
        GList *row_children = gtk_container_get_children(GTK_CONTAINER(row));
        for (GList *child_iter = row_children; child_iter != NULL; child_iter = child_iter->next) {
            GtkWidget *child = GTK_WIDGET(mx_gtk_find_child(child_iter->data, "chat_name"));
            if(mx_strlen(entry_text) == 0) {
                gtk_widget_show(GTK_WIDGET(row));
                continue;
            }
            if(mx_strstr(gtk_label_get_text(GTK_LABEL(child)), entry_text) != 0) {
                gtk_widget_show(GTK_WIDGET(row));
            }
            else
                gtk_widget_hide(GTK_WIDGET(row));
        }
        g_list_free(row_children);
    }
}

void mx_callback_group_info(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    // GList *children = gtk_container_get_children(GTK_CONTAINER(button));

    gtk_container_foreach(GTK_CONTAINER(app->scenes->group_info_dwindow->l_sc_members), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *group_image = app->scenes->chat_scene->img_chat;
    // GtkLabel *chat_label = GTK_LABEL(app->scenes->chat_scene->l_chatname);

    // gtk_label_set_text(GTK_LABEL(app->scenes->group_info->), gtk_label_get_text(chat_label));
    mx_log_err(SYSLOG, (char*)gtk_widget_get_name(app->scenes->chat_scene->img_chat)); // TODO: temp
    mx_set_image_widget_size(GTK_IMAGE(app->scenes->group_info_dwindow->img_group), app->scenes->group_info_dwindow->img_group, gtk_widget_get_name(group_image));

    mx_handler_ping_server_get_group_members(app);
    g_timeout_add_seconds(PING_SERVER_LONG_INTERVAL_SECONDS, mx_handler_ping_server_get_group_members, app);
}
