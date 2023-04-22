#include "client.h"

void mx_add_css_class(GtkWidget *widget, const char *classname) {
    GtkStyleContext *context;
    context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, classname);
}
