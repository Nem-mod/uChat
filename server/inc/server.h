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

#define IP "127.0.0.1"
#define CERTPATH "server/cert+key/server.crt"
#define KEYPATH "server/cert+key/server.key"
