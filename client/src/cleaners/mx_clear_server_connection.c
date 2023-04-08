#include "client.h"

void mx_clear_server_connection(t_serv_connection* s_con) {
    mx_log_info(SYSLOG, "Close listener thread");
    pthread_cancel(s_con->listener_thread);
    free(s_con);
}
