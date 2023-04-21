#include "client.h"

void mx_callback_hide_window_crt(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data; 

    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
}


void mx_init_create_group(t_uchat_application* app) {
    g_signal_connect(app->scenes->create_group_dwindow->b_close , "clicked", G_CALLBACK (mx_callback_hide_window_crt), app);
    g_signal_connect(app->scenes->create_group_dwindow->b_create_group, "clicked", G_CALLBACK(mx_callback_create_group), app);
}
