#include "client.h"

void mx_create_scenes(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, "client/Resources/gui/builder.ui", &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    app->scenes = malloc(sizeof(t_uchat_scenes));
    mx_init_scene_signin(builder, app);
    mx_init_scene_signup(builder, app);
}
