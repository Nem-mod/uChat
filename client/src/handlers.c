#include "client.h"

t_response *get_res(char* json) {
    struct json_object *jobj;
    jobj = json_tokener_parse(json);
    struct json_object *jtype = json_object_object_get(jobj, "type"); 
    struct json_object *jurl = json_object_object_get(jobj, "url");
    struct json_object *jprop = json_object_object_get(jobj, "prop"); 
    struct json_object *jstatus = json_object_object_get(jobj, "status"); 
    t_response* response_s = malloc(sizeof(t_response));

    response_s->type = json_object_get_string(jtype);
    response_s->url = json_object_get_string(jurl);
    response_s->property = json_object_get_string(jprop);
    response_s->status = mx_atoi(json_object_get_string(jstatus));

    return response_s;
}

int main_handler(char* json, t_uchat_application* app) {
    (void)app;
    t_response* res = get_res(json);

    if (mx_strcmp(res->url, "/auth/register") == 0 && res->status == 200) {
        mx_log_info(SYSLOG, "Registration success");
        mx_log_info(SYSLOG, mx_itoa(*(t_SCENE*)app->scenes->signup_scene->cbdata->data));
        gdk_threads_add_idle((GSourceFunc)mx_gfunc_change_scenes, app->scenes->signup_scene->cbdata);
    } else if (mx_strcmp(res->url, "/auth/register") == 0)
        mx_log_info(SYSLOG, "Registration failed");
    return res->status;

    // api->get("/users/", api->req, api->res, NULL, getAll_users);
    // api->get("/users/name:", api->req, api->res, NULL, get_users_by_name);


    // api->post("/contact/", api->req, api->res, NULL, add_contact);

    // api->get("/group/", api->req, api->res, NULL, get_group);
    // api->post("/group/", api->req, api->res, NULL, create_group);
    // api->delete("/group/", api->req, api->res, NULL, delete_group);

    // api->get("/group/members", api->req, api->res, NULL, get_group_members);
    // api->post("/group/members", api->req, api->res, NULL, insert_group_members);


    // api->get("/group/message", api->req, api->res, NULL, get_messages);
    // api->post("/group/message", api->req, api->res, NULL, create_message);

    // api->get("/auth/me", api->req, api->res, login_validation, login);
    // api->post("/auth/register", api->req, api->res, register_validation, registration);
}
