#include "client.h"

void calla(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application* app = (t_uchat_application*)data;
    g_print("%s",  gtk_widget_get_name(GTK_WIDGET( button)));

    struct json_object* jobj = json_object_new_object();
    json_object_object_add(jobj, "group_id", json_object_new_string(gtk_widget_get_name(GTK_WIDGET( button))));
    mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/group/message", jobj));
}


void mx_display_chat(t_uchat_application* app, t_response* res) {
    if(res){}
    

    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    GtkWidget *chat_box = mx_get_widget(builder, "chat_box");
    GtkWidget *chat_button = mx_get_widget(builder, "chat_button");
    GtkWidget *chat_img = mx_get_widget(builder, "chat_img");
    GtkWidget *chat_name = mx_get_widget(builder, "chat_name");

    struct json_object* jobj = json_tokener_parse(res->property);
    if(res->property == NULL) 
        return;
    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    if(mx_check_widget_exist(app->scenes->chat_scene->l_sc_chats, json_object_get_string(jgroup_id)))
        return;
    struct json_object *jname;
    char* file_name = RESOURCE_BASE_ICON;
    if(mx_strstr(res->property, "group_name"))
        jname = json_object_object_get(jobj, "group_name"); 
    else
        jname = json_object_object_get(jobj, "nick_name"); 

    if(mx_strstr(res->property, "file_name")) {
        struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
        file_name = (char*)json_object_get_string(jfname);
    }
    
    
    gtk_label_set_text(GTK_LABEL(chat_name), (char*)json_object_get_string(jname));
    gtk_widget_set_name(chat_button,  mx_itoa(json_object_get_int(jgroup_id)));
    gtk_image_set_from_file(GTK_IMAGE(chat_img), file_name);
    gtk_widget_set_size_request(chat_box, 10, 10);
    gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats), chat_button, -1);
    g_signal_connect(chat_button, "clicked", G_CALLBACK (calla), app);
    g_object_unref(builder);
}

