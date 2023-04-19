#include "client.h"

void mx_callback_hide_window(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data; 

    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
}
