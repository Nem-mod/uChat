#include "client.h"

gboolean mx_handler_chat_scroll_down(gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data;
    GtkAdjustment* adjustment = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(app->scenes->chat_scene->v_sc_messages));

    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    
    return false;
}
