#include "client.h"


void mx_callback_choose_file(GtkFileChooserButton *button, gpointer data) {
    t_uchat_application* app = (t_uchat_application*)data;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(button);
    GtkFileChooserAction action = gtk_file_chooser_get_action(chooser);
    if(app->choosed_file_pname != NULL) {
            mx_strdel(&app->choosed_file_pname);
    }
    if (action == GTK_FILE_CHOOSER_ACTION_OPEN) {
        
        gchar *filename = gtk_file_chooser_get_filename(chooser);
        app->choosed_file_pname = mx_strdup((char*)filename);
        g_free(filename);
    }
    g_print("Selected file %s\n", app->choosed_file_pname);
}
