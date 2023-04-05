#include "server.h"

const char* create_json_response(t_response *res) {
    struct json_object *jobj = json_object_new_object();
    json_object_object_add(jobj, "type", json_object_new_string(res->type));
    json_object_object_add(jobj, "url", json_object_new_string(res->url));
    json_object_object_add(jobj, "status", json_object_new_int(res->status));
    struct json_object *jprop = json_tokener_parse(res->property);
    json_object_object_add(jobj, "property",jprop );
    const char *json_str = json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY);
    return json_str;
}
