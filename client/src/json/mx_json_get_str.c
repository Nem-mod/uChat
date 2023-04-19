#include "client.h"

char* mx_json_get_str(const char* property, char* id) {
    json_object* jobj = json_tokener_parse(property);

    struct json_object *jstr = json_object_object_get(jobj, id);
    
    return (char*)json_object_get_string(jstr);
}
