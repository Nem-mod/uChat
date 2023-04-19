#include "client.h"

gboolean mx_handler_display_messages(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    //mx_display_chat(cbdata->app, (t_response*)cbdata->data);
    mx_handle_messages_res(cbdata->app, (t_response*)cbdata->data);
    return false;
}


