#include "client.h"

GtkWidget *mx_get_widget(GtkBuilder *builder, char *id) {
    GtkWidget *out = GTK_WIDGET(gtk_builder_get_object(builder, id));
    
    return out;
}
