#include "client.h"

int mx_main_handler(char* json, t_uchat_application* app) {
    t_response* res = mx_get_response(json);

    if(res->property == NULL)
        return 400;

    if (mx_strcmp(res->url, "/auth/me") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Auth success");
        
        gtk_label_set_text(GTK_LABEL(app->scenes->signin_scene->l_err_msg), "");
        gtk_label_set_text(GTK_LABEL(app->scenes->user_profile_dwindow->l_user_login ), mx_json_get_string(res->property, "login"));
        t_callback_data* cb = mx_create_callback_data(app, res);
        gdk_threads_add_idle(mx_handler_change_scene, app->scenes->chat_scene->cbdata);
        gdk_threads_add_idle(mx_handler_auth, cb);
        app->user_id = mx_json_get_int(res->property, "user_id");
        
        if(app->user_id != 0) {
            g_timeout_add_seconds(PING_SERVER_LONG_INTERVAL_SECONDS, mx_handler_ping_server_get_chats, app);
            g_timeout_add(PING_SERVER_SHORT_INTERVAL_MILISECONDS, mx_handler_ping_server_get_messages, app);
        }

        mx_handler_hide_chatbox(app);
        
        struct json_object *jobj = json_object_new_object();
        json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
        mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/user/groups", jobj)); // TODO: wrap all requests in funcs

    } else if (mx_strcmp(res->url, "/auth/me") == 0) {
        mx_log_err(SYSLOG, "Auth is failed");
        gtk_label_set_text(GTK_LABEL(app->scenes->signin_scene->l_err_msg), "Wrong login or password");
    }
        
    if (mx_strcmp(res->url, "/auth/register") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Registration success");
        gdk_threads_add_idle(mx_handler_change_scene, app->scenes->signin_scene->cbdata);
    } else if (mx_strcmp(res->url, "/auth/register") == 0) {
        gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_login_err), "Login taken");
        mx_log_err(SYSLOG, "Registration is failed");
    }

    if (mx_strcmp(res->url, "/user/groups") == 0 && res->status == 200) {
        t_callback_data* cb = mx_create_callback_data(app, res);
        gdk_threads_add_idle(mx_handler_create_new_chat_widget, cb);
    } else if (mx_strcmp(res->url, "/user/groups") == 0)
        mx_log_err(SYSLOG, "Get grp is failed");

    if (mx_strcmp(res->url, "/group/message") == 0 && res->status == 200 && mx_strcmp(res->type, "GET") == 0) {
        t_callback_data* cb = mx_create_callback_data(app, res);
        gdk_threads_add_idle(mx_handler_display_messages, cb);
    } else if (mx_strcmp(res->url, "/group/message") == 0 && mx_strcmp(res->type, "GET") == 0)
        mx_log_err(SYSLOG, "Get msg is failed");

    if (mx_strcmp(res->url, "/group/members") == 0 && res->status == 200 && mx_strcmp(res->type, "GET") == 0) {
        t_callback_data* cb = mx_create_callback_data(app, res);
        gdk_threads_add_idle(mx_handler_create_new_member_widget, cb);
    } else if (mx_strcmp(res->url, "/group/members") == 0 && mx_strcmp(res->type, "GET") == 0) 
        mx_log_err(SYSLOG, "Get group members failed");

    // if (mx_strcmp(res->url, "/"))

    

    //gdk_threads_add_idle(mx_clear_res, res);
    return 0;
}

void mx_handle_messages_res(t_uchat_application* app, t_response* res) {

    GtkWidget *message_box;
    GtkWidget *message_button_box;
    GtkWidget *message_img;
    GtkWidget *message_text_label;
    GtkWidget *message_user_nick_name;
    GtkWidget *message_sent_time_label;

    struct json_object* jobj = json_tokener_parse(res->property);
    if(res->property == NULL) 
        return;
    struct json_object *jmessage_id = json_object_object_get(jobj, "message_id"); 
    app->last_message_id = json_object_get_int(jmessage_id);
    if(mx_check_widget_exist(app->scenes->chat_scene->l_sc_messages, json_object_get_string(jmessage_id), NULL) != NULL)
        return;

    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }
    if (json_object_get_int(json_object_object_get(jobj, "user_id")) == app->user_id) {
        message_box = mx_get_widget(builder, "message_box1");
        message_button_box = mx_get_widget(builder, "message_button_box_user");
        message_img = mx_get_widget(builder, "message_img1");
        message_text_label = mx_get_widget(builder, "message_text_label1");
        message_user_nick_name = mx_get_widget(builder, " message_user_name1");
        message_sent_time_label = mx_get_widget(builder, "message_sent_time_label1");
    }
    else {
        message_box = mx_get_widget(builder, "message_box");
        message_button_box = mx_get_widget(builder, "message_button_box");
        message_img = mx_get_widget(builder, "message_img");
        message_text_label = mx_get_widget(builder, "message_text_label");
        message_user_nick_name = mx_get_widget(builder, " message_user_name");
        message_sent_time_label = mx_get_widget(builder, "message_sent_time_label");
    }

    

    struct json_object *jtext = json_object_object_get(jobj, "message_text");
    struct json_object *jnick_name = json_object_object_get(jobj, "user_nick_name");
    struct json_object *jsent_time = json_object_object_get(jobj, "sent_datatime");

    char* file_name = RESOURCE_BASE_ICON;
    if(mx_strstr(res->property, "file_name")) {
        struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
        file_name = (char*)json_object_get_string(jfname);
        // add gif
        if(mx_strstr(file_name, ".gif")) {
            GdkPixbufAnimation *animation = gdk_pixbuf_animation_new_from_file(mx_strjoin(RESOURCE_PATH, file_name), NULL);
            gtk_image_set_from_animation(GTK_IMAGE(message_img), animation);
        } 
        else
            mx_set_image_limit_size(GTK_IMAGE(message_img), message_img, mx_strjoin(RESOURCE_PATH, file_name));
        // gtk_image_set_from_file(GTK_IMAGE(message_img), mx_strjoin(RESOURCE_PATH, file_name));

    } else {
        gtk_container_remove(GTK_CONTAINER(message_box), message_img);
    }
    
    gtk_label_set_text(GTK_LABEL(message_text_label), (char*)json_object_get_string(jtext));
    gtk_label_set_text(GTK_LABEL(message_user_nick_name), (char*)json_object_get_string(jnick_name));
    gtk_label_set_text(GTK_LABEL(message_sent_time_label), (char*)json_object_get_string(jsent_time));

    gtk_widget_set_name(message_button_box,  mx_itoa(json_object_get_int(jmessage_id)));
    
    mx_set_style(message_box);
    mx_set_style(message_button_box);
    mx_set_style(message_img);
    mx_set_style(message_text_label);
    mx_set_style(message_user_nick_name);
    mx_set_style(message_sent_time_label);
    mx_add_css_class(message_box, "message-box");
    mx_add_css_class(message_button_box, "message");
    mx_add_css_class(message_user_nick_name, "message-user");
    mx_add_css_class(message_sent_time_label, "message-time");
    mx_add_css_class(message_text_label, "message-text");


    gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_messages), message_button_box, app->last_message_indx);

    mx_set_style(
        GTK_WIDGET(gtk_list_box_get_row_at_index(
            GTK_LIST_BOX(app->scenes->chat_scene->l_sc_messages),
            app->last_message_indx))
    );

    mx_add_css_class(
        GTK_WIDGET(gtk_list_box_get_row_at_index(
            GTK_LIST_BOX(app->scenes->chat_scene->l_sc_messages),
            app->last_message_indx)),
        "message-background"
    );
    
    app->last_message_indx += 1;
    
    gtk_widget_queue_draw(GTK_WIDGET(app->scenes->chat_scene->v_sc_messages));
    gdk_threads_add_idle(mx_handler_chat_scroll_down, app);
    
    //g_signal_connect(chat_button, "clicked", G_CALLBACK (mx_callback_chatbox), app);
    g_object_unref(builder);
}

gboolean mx_handler_auth(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data;
    t_uchat_application* app = cbdata->app;
    t_response* res = cbdata->data;

    // mx_auth_callback(cbdata->app, (t_response*)cbdata->data);
    struct json_object* jobj = json_tokener_parse(res->property);
    char* file_name = NULL;

    if(mx_strstr(res->property, "file_name")) {
        struct json_object *jfname = json_object_object_get(jobj, "file_name"); 

        file_name = (char*)json_object_get_string(jfname);
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(mx_strjoin(RESOURCE_PATH, file_name), 40, 40, NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(app->scenes->chat_scene->img_user), pixbuf);

        mx_set_image_widget_size(GTK_IMAGE(app->scenes->user_profile_dwindow->img_user), 
                                (app->scenes->user_profile_dwindow->img_user),  
                                mx_strjoin(RESOURCE_PATH, file_name));
    } else {
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(RESOURCE_BASE_ICON, 40, 40, NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(app->scenes->chat_scene->img_user), pixbuf);

        mx_set_image_widget_size(GTK_IMAGE(app->scenes->user_profile_dwindow->img_user), 
                                (app->scenes->user_profile_dwindow->img_user),  
                                RESOURCE_BASE_ICON);
    }

    return false;
}

gboolean mx_handler_change_scene(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_change_scenes(cbdata->app, *(t_SCENE*)cbdata->data);

    return false;
}

gboolean mx_handler_chat_scroll_down(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    GtkAdjustment* adjustment = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(app->scenes->chat_scene->v_sc_messages));

    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    
    return false;
}

gboolean mx_handler_create_new_chat_widget(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_create_new_chat_widget(cbdata->app, (t_response*)cbdata->data);

    return false;
}

gboolean mx_handler_create_new_member_widget(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_create_new_member_widget(cbdata->app, (t_response*)cbdata->data);

    return false;
}

gboolean mx_handler_display_messages(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    //mx_create_new_chat_widget(cbdata->app, (t_response*)cbdata->data);
    mx_handle_messages_res(cbdata->app, (t_response*)cbdata->data);

    return false;
}

gboolean mx_handler_ping_server_get_chats(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    struct json_object *jobj = json_object_new_object();

    if (app->user_id == 0)
        return false;

    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));

    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/user/groups", jobj));

    return true;
}

gboolean mx_handler_ping_server_get_messages(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    if (app->user_id == 0)
        return false;

    if (app->current_group_id != 0) {
        struct json_object *jobj = json_object_new_object();

        json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));
        json_object_object_add(jobj, "message_id", json_object_new_int(app->last_message_id));
    
        mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/message", jobj));
        // mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/members", jobj));
    }

    return true;
}

gboolean mx_handler_ping_server_get_group_members(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    if (app->active_scene != GROUP_INFO)
        return false;

    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));

    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/members", jobj));

    return true;
}

void mx_handler_hide_chatbox(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    
    gtk_widget_hide(app->scenes->chat_scene->img_chat);
    gtk_widget_hide(app->scenes->chat_scene->l_chatname);
    gtk_widget_hide(app->scenes->chat_scene->w_sc_messages);
    // gtk_widget_hide(app->scenes->chat_scene->v_sc_messages);
    // gtk_widget_hide(app->scenes->chat_scene->l_sc_messages);
    gtk_widget_hide(app->scenes->chat_scene->bc_file);
    gtk_widget_hide(app->scenes->chat_scene->e_f_chat);
    gtk_widget_hide(app->scenes->chat_scene->b_send_message);
    gtk_widget_hide(app->scenes->chat_scene->b_chat_settings);
}

void mx_handler_show_chatbox(gpointer data) {
        t_uchat_application *app = (t_uchat_application*)data;
    
    gtk_widget_show(app->scenes->chat_scene->img_chat);
    gtk_widget_show(app->scenes->chat_scene->l_chatname);
    gtk_widget_show(app->scenes->chat_scene->w_sc_messages);
    // gtk_widget_show(app->scenes->chat_scene->v_sc_messages);
    // gtk_widget_show(app->scenes->chat_scene->l_sc_messages);
    gtk_widget_show(app->scenes->chat_scene->bc_file);
    gtk_widget_show(app->scenes->chat_scene->e_f_chat);
    gtk_widget_show(app->scenes->chat_scene->b_send_message);
    gtk_widget_show(app->scenes->chat_scene->b_chat_settings);
}
