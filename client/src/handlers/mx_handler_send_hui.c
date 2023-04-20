#include "client.h"

gboolean mx_handler_send_hui(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;

    mx_log_info(SYSLOG, "send HUI is called!");

    struct json_object *jobj = json_object_new_object();

    // json_object_object_add(jobj, "message_text", json_object_new_string(message_text_entry));
    json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
    json_object_object_add(jobj, "group_id", json_object_new_int(app->current_group_id));
    // json_object_object_add(jobj, "sent_datatime", json_object_new_string(mx_get_formatted_time()));
    mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/user/groups", jobj));
    if (app->current_group_id != 0) // FIXME: CHANGE TO 0 AFTER MERGE
        mx_write_to_server(app->serv_connection->ssl,  mx_create_request("GET","/group/message", jobj));

    return true;
}
