#include "client.h"
char* mx_create_request(char* type, char* url, json_object* prop) {
    struct json_object *jobj = json_object_new_object();

    json_object_object_add(jobj, "type", json_object_new_string(type));
    json_object_object_add(jobj, "url", json_object_new_string(url));
    json_object_object_add(jobj, "property", prop);

    return (char*)json_object_to_json_string(jobj);
}

