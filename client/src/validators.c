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

int mx_validate_password_digits(const char *password) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[0-9]", 0);
    if (ret != 0) {
        return 1;
    }

    ret = regexec(&regex, password, 0, NULL, 0);

    return ret;
}

int mx_validate_password_letters(const char *password) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[a-zA-Z]", 0);
    if (ret != 0) {
        return 1;
    }

    ret = regexec(&regex, password, 0, NULL, 0);

    return ret;
}
