#include "server.h"


t_request *get_req(char* json) {
    struct json_object *jobj;
    jobj = json_tokener_parse(json);
    struct json_object *jtype = json_object_object_get(jobj, "type"); 
    struct json_object *jurl = json_object_object_get(jobj, "url");
    struct json_object *jprop = json_object_object_get(jobj, "property");
    t_request* requst_s = malloc(sizeof(t_request));
    requst_s->type = json_object_get_string(jtype);
    requst_s->url = json_object_get_string(jurl);
    requst_s->property = json_object_to_json_string(jprop);
    return requst_s;
}

t_response *init_res(char* json){
    struct json_object *jobj;
    jobj = json_tokener_parse(json);
    struct json_object *jtype = json_object_object_get(jobj, "type"); 
    struct json_object *jurl = json_object_object_get(jobj, "url");
    t_response* response_s = malloc(sizeof(t_response));
    response_s->type = json_object_get_string(jtype);
    response_s->url = json_object_get_string(jurl);
    response_s->property = malloc(sizeof(char) * 4096);
    return response_s;
}

const char* main_handler(SSL* ssl, char* json){
    t_SERVER_API* api = malloc(sizeof(t_SERVER_API));
    api->req = get_req(json);
    api->res = init_res(json);
    api->get = &get;
    api->post = &post;
    api->patch = &patch;
    api->delete = &delete;

    api->get("/users/", api->req, api->res, NULL, getAll_users);
    api->get("/users/name:", api->req, api->res, NULL, get_users_by_name);


    api->post("/contact/", api->req, api->res, NULL, add_contact);

    api->get("/group/", api->req, api->res, NULL, get_group);
    api->post("/group/", api->req, api->res, NULL, create_group);
    api->delete("/group/", api->req, api->res, NULL, delete_group);

    api->get("/group/members", api->req, api->res, NULL, get_group_members);
    api->post("/group/members", api->req, api->res, NULL, insert_group_members);


    api->get("/group/message", api->req, api->res, NULL, get_messages);
    api->post("/group/message", api->req, api->res, NULL, create_message);

    api->get("/auth/me", api->req, api->res, login_validation, login);
    api->post("/auth/register", api->req, api->res, register_validation, registration);


    const char *json_res = create_json_response(api->res);
    mx_SSL_write(ssl, (char*)json_res);
    
    return json_res;
}
