#include "client.h"

void mx_handle_messages_res(t_uchat_application* app, t_response* res) {
    const gchar *path = "client/Resources/css/main.css";
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    GtkWidget *message_box = mx_get_widget(builder, "message_box");
    GtkWidget *message_button_box = mx_get_widget(builder, "message_button_box");
    GtkWidget *message_img = mx_get_widget(builder, "message_img");
    GtkWidget *messsage_text_label = mx_get_widget(builder, "message_text_label");
    GtkWidget *messsage_user_nick_name = mx_get_widget(builder, " message_user_name");
    GtkWidget *messsage_sent_time_label = mx_get_widget(builder, "message_sent_time_label");
    
    struct json_object* jobj = json_tokener_parse(res->property);
    if(res->property == NULL) 
        return;
    struct json_object *jmessage_id = json_object_object_get(jobj, "message_id"); 
    app->last_message_id = json_object_get_int(jmessage_id);
    if(mx_check_widget_exist(app->scenes->chat_scene->l_sc_messages, json_object_get_string(jmessage_id)))
        return;

    struct json_object *jtext = json_object_object_get(jobj, "message_text");
    struct json_object *jnick_name = json_object_object_get(jobj, "user_nick_name");
    struct json_object *jsent_time = json_object_object_get(jobj, "sent_datatime");

    char* file_name = RESOURCE_BASE_ICON;
    if(mx_strstr(res->property, "file_name")) {
        struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
        file_name = (char*)json_object_get_string(jfname);
        mx_set_image_limit_size(GTK_IMAGE(message_img), message_img, mx_strjoin(RESOURCE_PATH, file_name));
        // gtk_image_set_from_file(GTK_IMAGE(message_img), mx_strjoin(RESOURCE_PATH, file_name));

    } else {
        gtk_container_remove(GTK_CONTAINER(message_box), message_img);
    }
    
    gtk_label_set_text(GTK_LABEL(messsage_text_label), (char*)json_object_get_string(jtext));
    gtk_label_set_text(GTK_LABEL(messsage_user_nick_name), (char*)json_object_get_string(jnick_name));
    gtk_label_set_text(GTK_LABEL(messsage_sent_time_label), (char*)json_object_get_string(jsent_time));

    gtk_widget_set_name(message_button_box,  mx_itoa(json_object_get_int(jmessage_id)));
    mx_set_style(path, message_box);
    mx_set_style(path, message_button_box);
    mx_add_css_class(message_box, "message-box");
    mx_add_css_class(message_button_box, "message");


    gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_messages), message_button_box, app->last_message_indx);
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
        mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->img_user), 
                                (app->scenes->chat_scene->img_user),  
                                mx_strjoin(RESOURCE_PATH, file_name));

        mx_set_image_widget_size(GTK_IMAGE(app->scenes->user_profile_dwindow->img_user), 
                                (app->scenes->user_profile_dwindow->img_user),  
                                mx_strjoin(RESOURCE_PATH, file_name));
    } else {
        mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->img_user), 
                                (app->scenes->chat_scene->b_send_message),  
                                RESOURCE_BASE_ICON);

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

gboolean mx_handler_display_chat(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_display_chat(cbdata->app, (t_response*)cbdata->data);

    return false;
}

gboolean mx_handler_display_messages(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    //mx_display_chat(cbdata->app, (t_response*)cbdata->data);
    mx_handle_messages_res(cbdata->app, (t_response*)cbdata->data);
    return false;
}

gboolean mx_handler_ping_server_get_chats(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    struct json_object *jobj = json_object_new_object();
    
    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));

    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/user/groups", jobj));

    return true;
}

gboolean mx_handler_ping_server_get_messages(UNUSED gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    if (app->current_group_id != 0) {
        struct json_object *jobj = json_object_new_object();

        json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));
        json_object_object_add(jobj, "message_id", json_object_new_int(app->last_message_id));
    
        mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/message", jobj));
    }

    return true;
}

