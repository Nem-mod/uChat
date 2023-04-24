#include "client.h"

GtkWidget* mx_get_widget(GtkBuilder *builder, char *id) {
    GtkWidget *out = GTK_WIDGET(gtk_builder_get_object(builder, id));
    
    return out;
}

GtkWidget* mx_gtk_find_child(GtkWidget* parent, const gchar* name) {
    if (mx_strcmp((char*)gtk_widget_get_name((GtkWidget*)parent), (char*)name) == 0) { 
        return parent;
    }

    if (GTK_IS_BIN(parent)) {
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
        return mx_gtk_find_child(child, name);
    }

    if (GTK_IS_CONTAINER(parent)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
        while ((children = g_list_next(children)) != NULL) {
            GtkWidget* widget = mx_gtk_find_child(children->data, name);
            if (widget != NULL) {
                    return widget;
            }
        }
    }

    return NULL;
}

GtkWidget* mx_get_widget_from_list(GtkWidget* list, int index) {
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(list), index);
    GList *children = NULL;
    GtkWidget *member = NULL;
    
    if (row != NULL) {
        children = gtk_container_get_children(GTK_CONTAINER(row));
        member = children->data;
    }
    return member;
}
