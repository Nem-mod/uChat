#include "client.h"

int mx_get_user_data(char* property) {
    json_object* jobj = json_tokener_parse(property);
    struct json_object *juser_id = json_object_object_get(jobj, "user_id");
    return json_object_get_int(juser_id);
}
int mx_main_handler(char* json, t_uchat_application* app) {
    t_response* res = mx_get_response(json);

    if (mx_strcmp(res->url, "/auth/me") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Auth success");
        app->user_id  = mx_get_user_data((char*)res->property);
        gdk_threads_add_idle((GSourceFunc)mx_handler_change_scene, app->scenes->chat_scene->cbdata);
    } else if (mx_strcmp(res->url, "/auth/me") == 0) {
        mx_log_err(SYSLOG, "Auth is failed");
    }
        
    if (mx_strcmp(res->url, "/auth/register") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Registration success");
        gdk_threads_add_idle((GSourceFunc)mx_handler_change_scene, app->scenes->signin_scene->cbdata);
    } else if (mx_strcmp(res->url, "/auth/register") == 0)
        mx_log_err(SYSLOG, "Registration is failed");

    


    return res->status;
}
