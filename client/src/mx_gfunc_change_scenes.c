#include "client.h"

gboolean mx_gfunc_change_scenes(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_log_info(SYSLOG, "Change scenes gfunc");
    mx_log_info(SYSLOG, mx_itoa(*(t_SCENE*)cbdata->data));
    mx_change_scenes(cbdata->app, *(t_SCENE*)cbdata->data);

    return false;
}
