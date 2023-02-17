#pragma once

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "log_utils.h"
#include "ssl_utils.h"
#include "connect_utils.h"

void mx_init_daemon();
