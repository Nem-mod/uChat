#include "server.h"

int register_validation(const char* req) {
    struct json_object *jobj;
    jobj = json_tokener_parse(req);
    struct json_object *jtemp = json_object_object_get(jobj, "login");
    if(json_object_get_string_len(jtemp) > 20) {
        mx_log_info(SYSLOG, "Registration failure: incorrect login");
        return 1;
    }
    jtemp = json_object_object_get(jobj, "password");
    if(json_object_get_string_len(jtemp) > 18) {
        mx_log_info(SYSLOG, "Registration failure: incorrect password");
        return 1;
    }
    jtemp = json_object_object_get(jobj, "first_name");
    if(json_object_get_string_len(jtemp) > 30) {
        mx_log_info(SYSLOG, "Registration failure: incorrect name");
        return 1;
    }
    jtemp = json_object_object_get(jobj, "last_name");
    if(json_object_get_string_len(jtemp) > 30) {
        mx_log_info(SYSLOG, "Registration failure: incorrect name");
        return 1;
    }
    return 0;
}

int login_validation(const char* req) {
    struct json_object *jobj;
    jobj = json_tokener_parse(req);
    struct json_object *jtemp = json_object_object_get(jobj, "login");
    if(json_object_get_string_len(jtemp) > 20) {
        mx_log_info(SYSLOG, "Registration failure: incorrect login");
        return 1;
    }
    jtemp = json_object_object_get(jobj, "password");
    if(json_object_get_string_len(jtemp) > 18) {
        mx_log_info(SYSLOG, "Registration failure: incorrect password");
        return 1;
    }
    return 0;
}

