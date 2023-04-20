#include "client.h"

void mx_callback_test(UNUSED GtkButton *button, UNUSED gpointer data) {
    mx_log_info(SYSLOG, "CALLBACK TEST is called!");
}
