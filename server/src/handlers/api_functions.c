#include "server.h"

int get(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
    if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "GET")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
        controller(req->property, res->property);
        res->status = SUCCESSFUL_RES;
    } 
    else {
        controller(req->property, res->property);
        res->status = SERVER_ERR_RES;
    }
    return 0;
}

int post(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
   if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "POST")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
        if(controller(req->property, res->property) == -1){
            res->status = BAD_REQ;
        } 
        else
            res->status = SUCCESSFUL_RES;
    } 
    else {
        controller(req->property, res->property);
        res->status = SERVER_ERR_RES;
    }
    return 0;
}

int patch(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
    if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "PATCH")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
        controller(req->property, res->property);
        res->status = SUCCESSFUL_RES;
    } 
    else {
        controller(req->property, res->property);
        res->status = SERVER_ERR_RES;
    }

    return 0;
}

int delete(char* url,  t_request* req, t_response* res, t_validator validator, t_controller  controller) {
    if(mx_strcmp(url, req->url) || mx_strcmp(req->type, "DELETE")) {
        return 1;
    }

    if(validator == NULL || validator(req->property) != 1) {
        controller(req->property, res->property);
        res->status = SUCCESSFUL_RES;
    } 
    else {
        controller(req->property, res->property);
        res->status = SERVER_ERR_RES;
    }
    return 0;
}
