#pragma once

#include <unistd.h>

#include "server_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"
#include "libdb.h"

#define IP "127.0.0.1"
#define CERTPATH "server/cert+key/server.crt"
#define KEYPATH "server/cert+key/server.key"
