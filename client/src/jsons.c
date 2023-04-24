#include "client.h"

char* mx_create_request(char* type, char* url, json_object* prop) {
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "type", json_object_new_string(type));
    json_object_object_add(jobj, "url", json_object_new_string(url));
    json_object_object_add(jobj, "property", prop);
    char* out = (char*)json_object_to_json_string(jobj);
    return  out;
}

t_response *mx_get_response(char* json) {
    struct json_object *jobj;
    jobj = json_tokener_parse(json);
    struct json_object *jtype = json_object_object_get(jobj, "type"); 
    struct json_object *jurl = json_object_object_get(jobj, "url");
    struct json_object *jprop = json_object_object_get(jobj, "property"); 
    struct json_object *jstatus = json_object_object_get(jobj, "status"); 
    t_response* response_s = malloc(sizeof(t_response));

    response_s->type = json_object_get_string(jtype);
    response_s->url = json_object_get_string(jurl);
    response_s->property = json_object_get_string(jprop);
    response_s->status = mx_atoi(json_object_get_string(jstatus));

    return response_s;
}

int mx_json_get_int(const char* property, const char* obj) {
    json_object* jobj = json_tokener_parse(property);

    struct json_object *jint = json_object_object_get(jobj, obj);

    return json_object_get_int(jint);
}

char* mx_json_get_string(const char* property, const char* obj) {
    json_object* jobj = json_tokener_parse(property);

    struct json_object *jstr = json_object_object_get(jobj, obj);

    return (char*)json_object_get_string(jstr);
}
