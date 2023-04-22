#include "client.h"

int mx_get_user_data(char* property) {
    json_object* jobj = json_tokener_parse(property);
    struct json_object *juser_id = json_object_object_get(jobj, "user_id");
    return json_object_get_int(juser_id);
}

int mx_main_handler(char* json, t_uchat_application* app) {
    t_response* res = mx_get_response(json);

    if(res->property == NULL)
        return 400;

    if (mx_strcmp(res->url, "/auth/me") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Auth success");
        
        gtk_label_set_text(GTK_LABEL(app->scenes->signin_scene->l_err_msg), "");
        t_callback_data* cb = mx_create_callback_data(app, res);
        gdk_threads_add_idle(mx_handler_change_scene, app->scenes->chat_scene->cbdata);
        gdk_threads_add_idle(mx_handler_auth, cb);
        app->user_id  = mx_get_user_data((char*)res->property);
        
        if(app->user_id != 0) {
            g_timeout_add_seconds(PING_SERVER_LONG_INTERAL_SECONDS, mx_handler_ping_server_get_chats, app);
            g_timeout_add(PING_SERVER_SHORT_INTERVAL_MILISECONDS, mx_handler_ping_server_get_messages, app);
        }
        
        struct json_object *jobj = json_object_new_object();
        json_object_object_add(jobj, "user_id", json_object_new_int(app->user_id));
        mx_write_to_server(app->serv_connection->ssl, mx_create_request("GET", "/user/groups", jobj));

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
        // mx_log_info(SYSLOG, "Get grp  success");
        gdk_threads_add_idle(mx_handler_display_chat, cb);
    } else if (mx_strcmp(res->url, "/user/groups") == 0)
        mx_log_err(SYSLOG, "Get grp is failed");

    if (mx_strcmp(res->url, "/group/message") == 0 && res->status == 200 && mx_strcmp(res->type, "GET") == 0) {
        t_callback_data* cb = mx_create_callback_data(app, res);
        // mx_log_info(SYSLOG, "Get msg  success");
        gdk_threads_add_idle(mx_handler_display_messages, cb);
    } else if (mx_strcmp(res->url, "/group/message") == 0 && mx_strcmp(res->type, "GET") == 0)
        mx_log_err(SYSLOG, "Get msg is failed");

    // if (mx_strcmp(res->url, "/"))

    


    return res->status;
}
