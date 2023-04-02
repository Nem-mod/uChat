#pragma once

#include <stdio.h>
#include <unistd.h>

#include <gtk/gtk.h>

#include "client_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"

#define     IP "127.0.0.1"
#define CERTPATH "client/cert+key/client.crt"
#define KEYPATH "client/cert+key/client.key"
