#include "server.h"

int get(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
    if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "GET")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
         if(controller(req->property, &res->property) == -1){
           struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
            res->status = BAD_REQ;
            
        } 
        else
            res->status = SUCCESSFUL_RES;
    } 
    else {
       struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
        //controller(req->property, &res->property);
        res->status = SERVER_ERR_RES;
    }
    return 0;
}

int post(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
   if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "POST")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
        if(controller(req->property, &res->property) == -1){
            struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
            res->status = BAD_REQ;
        } 
        else
            res->status = SUCCESSFUL_RES;
    } 
    else {
       struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
        //controller(req->property, &res->property);
        res->status = SERVER_ERR_RES;
    }
    return 0;
}

int patch(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
    if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "PATCH")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
         if(controller(req->property, &res->property) == -1){
           struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
            res->status = BAD_REQ;
        } 
        else
            res->status = SUCCESSFUL_RES;
    } 
    else {
       struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
        //controller(req->property, &res->property);
        res->status = SERVER_ERR_RES;
    }

    return 0;
}

int delete(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
    if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "DELETE")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
         if(controller(req->property, &res->property) == -1){
           struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
            res->status = BAD_REQ;
        } 
        else
            res->status = SUCCESSFUL_RES;
    } 
    else {
       struct json_object *jobj = json_tokener_parse(req->property);
            json_object_object_add(jobj, "message", json_object_new_string("ERROR"));
            char *err = (char*)json_object_to_json_string(jobj);
            res->property = err;
        //controller(req->property, &res->property);
        res->status = SERVER_ERR_RES;
    }
    return 0;
}
