#pragma once

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ssl_utils.h"
#include "log_utils.h"

#define SERVER 1
#define CLIENT 0

void mx_init_daemon();

void* mx_create_server_client_session(void *server_ssl);
