#include "client.h"

int mx_main_handler(char* json, t_uchat_application* app) {
    t_response* res = mx_get_response(json);

    if (mx_strcmp(res->url, "/auth/me") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Auth success");
        
        gdk_threads_add_idle((GSourceFunc)mx_handler_change_scene, app->scenes->chat_scene->cbdata);
    } else if (mx_strcmp(res->url, "/auth/me") == 0) {
        mx_log_err(SYSLOG, "Auth is failed");
    }
        
    if (mx_strcmp(res->url, "/auth/register") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Registration success");
        
        gdk_threads_add_idle((GSourceFunc)mx_handler_change_scene, app->scenes->signup_scene->cbdata);
    } else if (mx_strcmp(res->url, "/auth/register") == 0)
        mx_log_err(SYSLOG, "Registration is failed");

    


    return res->status;
}
