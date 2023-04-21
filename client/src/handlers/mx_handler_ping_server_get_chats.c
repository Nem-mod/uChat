#include "client.h"

gboolean mx_handler_ping_server_get_chats(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    struct json_object *jobj = json_object_new_object();
    
    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));

    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/user/groups", jobj));

    return true;
}
