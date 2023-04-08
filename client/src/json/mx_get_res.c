#include "client.h"

t_response *mx_get_response(char* json) {
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
