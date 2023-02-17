#pragma once

#include <sys/time.h>
#include <stdio.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
// #include <openssl/rsa.h>
// #include <openssl/x509.h>
// #include <openssl/evp.h>

#include "libmx.h"

#define SYSLOG "server_log.txt"

char* mx_get_formatted_time();

void mx_log_SSL_errors(char* file);

void mx_log_msg(char* file, char* str);

void mx_log_err(char* file, char* str);

void mx_log_info(char* file, char* str);
