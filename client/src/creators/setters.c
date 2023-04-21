#include "client.h"

void mx_set_image_widget_size(GtkImage* image, GtkWidget* widget_to_shrink, const char* filename) {
    int widget_width;
    int widget_height;

    gtk_widget_get_size_request(widget_to_shrink, &widget_width, &widget_height);

    // mx_log_info(SYSLOG, "Image info: width, height, path vvv" );
    // mx_log_info(SYSLOG, mx_itoa(widget_width));
    // mx_log_info(SYSLOG, mx_itoa(widget_height));
    // mx_log_info(SYSLOG, (char*)filename);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(filename, widget_width, widget_height, NULL);

    gtk_image_set_from_pixbuf(image, pixbuf);
}

void mx_set_style(const gchar *path, GtkWidget *widget) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, path, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}
