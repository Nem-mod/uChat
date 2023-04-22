#include "client.h"

// TODO: clear other structs

void mx_clear_app(UNUSED GtkWindow *window, void* data) {
    t_uchat_application* app = (t_uchat_application*)data;

    mx_log_info(SYSLOG, "Close ssl connection");
    mx_SSL_write(app->serv_connection->ssl, ":exit");

    mx_clear_server_connection(app->serv_connection);
    free(app);

    mx_log_info(SYSLOG, "Close application");
    gtk_main_quit();
    exit(0);
}

void mx_clear_entry(GtkEntry *entry) {
    gtk_entry_set_text(entry, "");
}

void mx_clear_server_connection(t_serv_connection* s_con) {
    mx_log_info(SYSLOG, "Close listener thread");
    pthread_cancel(s_con->listener_thread);
    free(s_con);
}