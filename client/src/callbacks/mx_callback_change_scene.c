#include "client.h"

void mx_callback_change_scene(UNUSED GtkButton *button, gpointer data) {
    t_callback_data *cbdata = (t_callback_data*)data; 

    mx_change_scenes(cbdata->app, *(t_SCENE*)cbdata->data);
}
