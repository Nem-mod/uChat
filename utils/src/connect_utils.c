#include "../inc/connect_utils.h"

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

int mx_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);

    if (res == -1) {
        mx_log_err(SYSLOG, "connect failed");
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
