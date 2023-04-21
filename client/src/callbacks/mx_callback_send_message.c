#include "client.h"


void mx_callback_send_message(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    if(app->current_group_id == 0) 
        return;
    
    int message_len = gtk_entry_get_text_length(GTK_ENTRY(app->scenes->chat_scene->e_f_chat)); 
    if(message_len <= 0 || message_len > 256) {return;}
    char *message_text_entry = (char*)gtk_entry_get_text(GTK_ENTRY(app->scenes->chat_scene->e_f_chat));
    g_print("%d", message_len);
    
  
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
    
    if(app->choosed_file_pname != NULL) {
            mx_strdel(&app->choosed_file_pname);
    }
    //mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/message", jobj));
}
