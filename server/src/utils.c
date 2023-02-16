#include "../inc/server.h"

int mx_create_socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);

    if (res == -1) {
        mx_log_err(SYSLOG, "socket failed");
        exit(EXIT_FAILURE);
    }

    return res;
}

void mx_bind_socket_to_address(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);

    if (res == -1) {
        mx_log_err(SYSLOG, "bind failed");
        exit(EXIT_FAILURE);
    }
}

void mx_listen_socket(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);

    if (res == -1) {
        mx_log_err(SYSLOG, "listen failed");
        exit(EXIT_FAILURE);
    }
}

int mx_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);

    if (res == -1) {
        mx_log_err(SYSLOG, "accept failed");
        exit(EXIT_FAILURE);
    }

    return res;
}

struct sockaddr_in mx_init_address(int port, char *ip, int family) {
    struct sockaddr_in addr = {0};

    addr.sin_family = family;
    addr.sin_port = htons(port);
    inet_pton(family, ip, &addr.sin_addr);

    return addr;
}

SSL_CTX* mx_init_context(bool is_server) {
    SSL_CTX *ctx;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    if (is_server)
        ctx = SSL_CTX_new(TLS_server_method());
    else
        ctx = SSL_CTX_new(TLS_client_method());

    if (ctx == NULL) {
        mx_log_err(SYSLOG, "Unable to create SSL context"); // Write in daemon file (need to create special function or already exist)
        mx_log_SSL_errors(SYSLOG);            // Same
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void mx_use_certificate_key(SSL_CTX *ctx, char *certPath, char *keyPath) {
    if (SSL_CTX_use_certificate_file(ctx, certPath, SSL_FILETYPE_PEM) <= 0) {
        mx_log_err(SYSLOG, "Unable to get certificate");    // Write in daemon file (need to create special function or already exist)
        mx_log_SSL_errors(SYSLOG); 
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, keyPath, SSL_FILETYPE_PEM) <= 0)  {
        mx_log_err(SYSLOG, "Unable to get private key");    // Write in daemon file (need to create special function or already exist)
        mx_log_SSL_errors(SYSLOG); 
        exit(EXIT_FAILURE);
    }
    if (!SSL_CTX_check_private_key(ctx)) {
        mx_log_err(SYSLOG, "Private key does not match the public certificate");  // Write in daemon file (need to create special function or already exist)
        exit(EXIT_FAILURE);
    }
}

SSL* mx_init_SSL_session(SSL_CTX* ctx, int socket) {
    SSL* ssl;

    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        mx_log_err(SYSLOG, "Unable to create SSL structure");    // Write in daemon file (need to create special function or already exist)
        mx_log_SSL_errors(SYSLOG);
        exit(EXIT_FAILURE);
    }
    if (SSL_set_fd(ssl, socket) == 0) {
        mx_log_err(SYSLOG, "Unable to link socket to SSL session");    // Write in daemon file (need to create special function or already exist)
        mx_log_SSL_errors(SYSLOG);
        exit(EXIT_FAILURE);
    }

    return ssl;
}

void mx_SSL_log_print_error(SSL* ssl, int erno) {    // Write in daemon file (need to create special function or already exist)
    if (erno != 1) {
        switch(SSL_get_error(ssl, erno)) {
            case SSL_ERROR_NONE:
                mx_log_err(SYSLOG, "error SSL_ERROR_NONE\n");
                break;
            case SSL_ERROR_SSL:
                mx_log_err(SYSLOG, "error SSL_ERROR_SSL\n");
                break;
            case SSL_ERROR_WANT_READ:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_READ\n");
                break;
            case SSL_ERROR_WANT_WRITE:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_WRITE\n");
                break;
            case SSL_ERROR_WANT_X509_LOOKUP:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_X509_LOOKUP\n");
                break;
            case SSL_ERROR_SYSCALL:
                mx_log_err(SYSLOG, "error SSL_ERROR_SYSCALL\n");
                break;
            case SSL_ERROR_ZERO_RETURN:
                mx_log_err(SYSLOG, "error SSL_ERROR_ZERO_RETURN \n");
                break;
            case SSL_ERROR_WANT_CONNECT:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_CONNECT\n");
                break;
            default:
                mx_log_err(SYSLOG, "error unknown\n");
                break;
        }
        mx_log_SSL_errors(SYSLOG); 
    }
}

int mx_handshake(SSL* ssl, int is_server) {    // Write in daemon file (need to create special function or already exist)
    int result;

    if (is_server)
        result = SSL_accept(ssl);
    else
        result = SSL_connect(ssl);

    if (result != 1) {
        mx_log_err(SYSLOG, "Handshake error");    // Write in daemon file (need to create special function or already exist)
        mx_SSL_log_print_error(ssl, result);

        return 0;
    }
    return 1;
}

int mx_SSL_write(SSL* ssl, char* buffer) {
    int result;

    result = SSL_write(ssl, buffer, mx_strlen(buffer) + 1);
    if (result <= 0) {
        mx_log_err(SYSLOG, "Unable to write msg");    // Write in daemon file (need to create special function or already exist)
        mx_SSL_log_print_error(ssl, result);
    }

    return result;
}

int mx_SSL_read(SSL* ssl, char* buffer) {
    int result;

    result = SSL_read(ssl, buffer, sizeof(buffer));
    if (result <= 0) {
        mx_log_err(SYSLOG, "Unable to read msg");    // Write in daemon file (need to create special function or already exist)
        mx_SSL_log_print_error(ssl, result);
    }

    return result;
}

void mx_init_daemon() {
    pid_t pid;
    struct rlimit flim;

    if ((pid = fork()) < 0)
        return;
    if (pid != 0) {
        printf("Daemon started with PID =%d\n", pid);
        exit(0);
    }
    setsid();
    chdir("/");
    
    getrlimit(RLIMIT_NOFILE, &flim);
    for (rlim_t i = 0; i < flim.rlim_max; i++)
        close(i);
}

char* mx_get_formatted_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char *str = mx_strnew(25);
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    mx_strcat(str, "[");
    mx_strcat(str, mx_itoa(timeinfo->tm_mday));
    mx_strcat(str, ".");
    mx_strcat(str, mx_itoa(timeinfo->tm_mon + 1));
    mx_strcat(str, ".");
    mx_strcat(str, mx_itoa(timeinfo->tm_year + 1900));
    mx_strcat(str, " | ");
    mx_strcat(str, mx_itoa(timeinfo->tm_hour));
    mx_strcat(str, ":");
    mx_strcat(str, mx_itoa(timeinfo->tm_min));
    mx_strcat(str, ":");
    mx_strcat(str, mx_itoa(timeinfo->tm_sec));
    mx_strcat(str, "]");

    return str;
}

void mx_log_SSL_errors(char* file) {
    FILE *fd;

    if ((fd = fopen(file, "a+")) == NULL) 
        return;
    ERR_print_errors_fp(fd);

    fclose(fd);
}

void mx_log_msg(char* file, char* str) {
    FILE *fd;
    char *time;

    if ((fd = fopen(file, "a+")) == NULL) 
        return;
    time = mx_get_formatted_time();

    fprintf(fd, "%s %s\n", time, str);

    fclose(fd);
    mx_strdel(&time);
}

void mx_log_err(char* file, char* str) {
    char *new_str = mx_strjoin("ERROR: ", str);

    mx_log_msg(file, new_str);
    mx_strdel(&new_str);
}

void mx_log_info(char* file, char* str) {
    char *new_str = mx_strjoin("INFO: ", str);

    mx_log_msg(file, new_str);
    mx_strdel(&new_str);
}
