#include "server.h"

char* mx_create_err_res(char* errMsg){
    struct json_object* jobj = json_object_new_object();
    struct json_object* j_errMsg = json_object_new_string(errMsg);
    json_object_object_add(jobj, "message", j_errMsg);
    return (char*)json_object_to_json_string(jobj);
}


