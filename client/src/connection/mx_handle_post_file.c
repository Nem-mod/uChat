#include "client.h"

unsigned long mx_handle_post_file(char* req, char** filename) {
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jtype = json_object_object_get(jobj, "type");
    if(mx_strcmp(json_object_get_string(jtype), "GET")){
        return 0;
    }

    struct json_object *jprop = json_object_object_get(jobj, "property");
    struct json_object *jfilename = json_object_object_get(jprop, "file_name");
    *filename = (char*)json_object_get_string(jfilename);
    struct json_object *jsize = json_object_object_get(jprop, "file_size");
    
    return json_object_get_uint64(jsize);
   
}
