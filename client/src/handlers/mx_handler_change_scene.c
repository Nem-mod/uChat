#include "client.h"

gboolean mx_handler_change_scene(gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_change_scenes(cbdata->app, *(t_SCENE*)cbdata->data);

    return false;
}
