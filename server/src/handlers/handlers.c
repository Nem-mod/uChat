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
    response_s->property = NULL;
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
    char *json_res;
   
    struct json_object *jobj = json_tokener_parse(api->res->property);
    // mx_log_info("jsf.txt",  "sss\n");
    
    if (json_object_is_type(jobj, json_type_array)) {
        mx_log_info(SYSLOG, "vvv Pass BIG JSON to the client vvv");
        mx_log_info(SYSLOG, (char*)json_object_to_json_string(jobj)); 

        for(size_t i = 0; i < json_object_array_length(jobj); i++) {
            struct json_object *jtmp = json_object_array_get_idx(jobj, i);
            json_res = (char*)create_json_response(api->res, (char*)json_object_to_json_string(jtmp));
            mx_SSL_write(ssl, (char*)json_res);
            struct json_object *jfname = json_object_object_get(jtmp, "file_name");
            struct json_object *jfsize = json_object_object_get(jtmp, "file_size");
            if(json_object_get_uint64(jfsize) > 0 && json_object_get_string(jfname)) {
                mx_SSL_sendfile(ssl, mx_strjoin("./" , (char*)json_object_get_string(jfname)), json_object_get_uint64(jfsize));
            }
            mx_strdel(&json_res);
        }
    } 
    else {
        json_res = (char*)create_json_response(api->res, (char*)(api->res->property));
        
        mx_log_info(SYSLOG, "vvv Pass JSON to the client vvv");
        mx_log_info(SYSLOG, (char*)json_res);

        mx_SSL_write(ssl, (char*)json_res);
    }
    
    if(api->res->property)
        mx_strdel(&api->res->property);
    return NULL;
}
