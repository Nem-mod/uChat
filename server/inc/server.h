#pragma once

#include <unistd.h>
#include <sys/time.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "server_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "db_utils.h"
#include "libmx.h"

#include "validations.h"
#include "handlers.h"

#define IP "127.0.0.1"
#define CERTPATH "server/cert+key/server.crt"
#define KEYPATH "server/cert+key/server.key"

typedef int   (*t_vallidator)(char* req);
typedef char* (*t_handleError)(char* req, char* res);
typedef int   (*t_cotroller)(char* req, char* res);
typedef int   (*t_rcallback)(char* type, t_vallidator validator, t_handleError handlerr, t_cotroller controller);

typedef struct s_requests {   
    char* type;
    t_rcallback call;
}              t_requests;
