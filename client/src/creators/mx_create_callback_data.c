#include "client.h"

t_callback_data* mx_create_callback_data(t_uchat_application* app, void* data) {
    t_callback_data* cbdata = malloc(sizeof(t_callback_data));

    cbdata->app = app;
    cbdata->data = data;
    
    return cbdata;
}
