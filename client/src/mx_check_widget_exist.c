#include "client.h"

int mx_check_widget_exist(GtkWidget *list_box, const char* desired_name) {
    for(guint row_index = 0;  row_index < g_list_length(gtk_container_get_children(GTK_CONTAINER(list_box))); row_index++){
        GtkListBoxRow *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(list_box), row_index);
        if (row != NULL) {
            GList *children = gtk_container_get_children(GTK_CONTAINER(row));
            //row_index++;
            for (GList *iter = children; iter != NULL; iter = iter->next) {
                GtkWidget *child = GTK_WIDGET(iter->data);
                const gchar *name = gtk_widget_get_name(child);
                // if already exist

                if (name != NULL && g_strcmp0(name, desired_name) == 0) {
                    return -1;
                    break;
                }
            }
        }
    }
   
    return 0;
}
