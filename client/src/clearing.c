#include "client.h"

// TODO: write other structs

void mx_clear_server_connection(t_serv_connection* s_con) {
    pthread_cancel(s_con->listener_thread);
    free(s_con);
}

void mx_clear_app(GtkWindow *window, void* data) {
    t_uchat_application* app = (t_uchat_application*)data;
    mx_SSL_write(app->serv_connection->ssl, ":exit");
    mx_clear_server_connection(app->serv_connection);
    free(app);
    (void)window;
    gtk_main_quit();
    exit(0);
}
