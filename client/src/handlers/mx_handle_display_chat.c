#include "client.h"

gboolean mx_handle_display_chat(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_display_chat(cbdata->app, (t_response*)cbdata->data);

    return false;
}

