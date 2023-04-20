#include "client.h"

unsigned long mx_handle_post_file(char* req, char** filename) {
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jtype = json_object_object_get(jobj, "type");
    if(mx_strcmp(json_object_get_string(jtype), "POST-FILE")){
        return 0;
    }
    struct json_object *jfilename = json_object_object_get(jobj, "file_name");
    *filename = (char*)json_object_get_string(jfilename);
    struct json_object *jsize = json_object_object_get(jobj, "file_size");
    mx_log_info(SYSLOG, (req));
    return json_object_get_uint64(jsize);
}
