#include "client.h"

int mx_json_get_int(const char* property, char* id) {
    json_object* jobj = json_tokener_parse(property);

    struct json_object *jint = json_object_object_get(jobj, id);
    
    return json_object_get_int(jint);
}
