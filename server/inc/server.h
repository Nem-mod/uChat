#pragma once

#include <unistd.h>
#include <sys/time.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <json.h>

#include "server_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "db_utils.h"
#include "libmx.h"
#include "validations.h"
#include "database_ex.h"
#include "controllers.h"
#include "tables.h"

#define IP "127.0.0.1"
#define CERTPATH "server/cert+key/server.crt"
#define KEYPATH "server/cert+key/server.key"

#define SEED 2454193
#define SUCCESSFUL_RES 200
#define BAD_REQ 400
#define NOT_FOUND 404
#define SERVER_ERR_RES 500
#define DATABASE_NAME "uchat.db"

typedef struct s_request {   
    const char* type;
    const char* url;
    const char* property;
    
}              t_request;

typedef struct s_response {   
    const char* type;
    const char* url;
    char* property;
    char* file;
    int file_size;
    int status;
    
}              t_response;

typedef int     (*t_validator)(const char* req);
typedef int     (*t_controller)(const char* req, char* res);
typedef int   (*Http_req)(char* url, t_request* req, t_response* res, t_validator validator, t_controller  controller);



typedef struct s_SERVER_API {   
    t_request* req;
    t_response* res;

    Http_req get;
    Http_req post;
    Http_req patch;
    Http_req delete;
    
}              t_SERVER_API;


const char* main_handler(SSL* ssl, char* json); 

int get(char* url, t_request* req,  t_response* res, t_validator validator, t_controller  controller);
int post(char* url, t_request* req,  t_response* res, t_validator validator, t_controller  controller);
int patch(char* url, t_request* req,  t_response* res, t_validator validator, t_controller  controller);
int delete(char* url, t_request* req,  t_response* res, t_validator validator, t_controller  controller);

t_request *get_req(char* json);
t_response *init_res(char* json);
const char* create_json_response(t_response *res);


char* create_token(int length);
char* mx_create_err_res(char* errMsg);
