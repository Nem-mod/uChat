#include "client.h"

void mx_handle_messages_res(t_uchat_application* app, t_response* res) {
    
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
    GtkWidget *messsage_sent_time_label = mx_get_widget(builder, "message_sent_time_label");

    struct json_object* jobj = json_tokener_parse(res->property);
    if(res->property == NULL) 
        return;
    struct json_object *jmessage_id = json_object_object_get(jobj, "message_id"); 
    app->last_message_id = json_object_get_int(jmessage_id);
    if(mx_check_widget_exist(app->scenes->chat_scene->l_sc_messages, json_object_get_string(jmessage_id)))
        return;

    struct json_object *jtext = json_object_object_get(jobj, "message_text");
    struct json_object *jsent_time = json_object_object_get(jobj, "sent_datatime");

    char* file_name = RESOURCE_BASE_ICON;
    if(mx_strstr(res->property, "file_name")) {
        struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
        file_name = (char*)json_object_get_string(jfname);
        gtk_image_set_from_file(GTK_IMAGE(message_img), mx_strjoin(RESOURCE_PATH, file_name));

    } else {
        gtk_container_remove(GTK_CONTAINER(message_box), message_img);
    }
    
    
    gtk_label_set_text(GTK_LABEL(messsage_text_label), (char*)json_object_get_string(jtext));
    gtk_label_set_text(GTK_LABEL(messsage_sent_time_label), (char*)json_object_get_string(jsent_time));

    gtk_widget_set_name(message_button_box,  mx_itoa(json_object_get_int(jmessage_id)));

    gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_messages), message_button_box, app->last_message_indx);
    app->last_message_indx += 1;
    
    gtk_widget_queue_draw(GTK_WIDGET(app->scenes->chat_scene->v_sc_messages));
    gdk_threads_add_idle(mx_handler_chat_scroll_down, app);
    
    //g_signal_connect(chat_button, "clicked", G_CALLBACK (mx_callback_chatbox), app);
    g_object_unref(builder);
}

