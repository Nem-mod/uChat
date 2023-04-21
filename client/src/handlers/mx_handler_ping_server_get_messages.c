#include "client.h"

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
