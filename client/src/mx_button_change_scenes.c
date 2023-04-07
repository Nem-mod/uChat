#include "client.h"

void mx_button_change_scenes(GtkButton *button, gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_log_info(SYSLOG, "Change scenes button pressed");
    // mx_printint((t_SCENE)cbdata->data);
    mx_change_scenes(cbdata->app, *(t_SCENE*)cbdata->data);
    (void)button;
}
