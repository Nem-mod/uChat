#include "client.h"

void mx_set_image_widget_size(GtkImage* image, GtkWidget* widget_to_shrink, const char* filename) {
    int widget_width;
    int widget_height;

    gtk_widget_get_size_request(widget_to_shrink, &widget_width, &widget_height);

    // //mx_log_info(SYSLOG, "Image info: width, height, path vvv" );
    // //mx_log_info(SYSLOG, mx_itoa(widget_width));
    // //mx_log_info(SYSLOG, mx_itoa(widget_height));
    // //mx_log_info(SYSLOG, (char*)filename);

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(filename, widget_width, widget_height, NULL);

    gtk_widget_set_size_request(widget_to_shrink, widget_width, widget_height);  
    gtk_image_set_from_pixbuf(image, pixbuf);
}

// void mx_set_gif_widget_size(GtkImage* image, GtkWidget* widget_to_shrink, const char* filename) {
//     int widget_width;
//     int widget_height;

//     GdkPixbufAnimation *animation = gdk_pixbuf_animation_new_from_file(RESOURCE_DANCING_CAT1_PATH, NULL);
//     gtk_image_set_from_animation(GTK_IMAGE(app->scenes->signin_scene->img_paw2), animation);

//     gtk_widget_get_size_request(widget_to_shrink, &widget_width, &widget_height);

//     // //mx_log_info(SYSLOG, "Image info: width, height, path vvv" );
//     // //mx_log_info(SYSLOG, mx_itoa(widget_width));
//     // //mx_log_info(SYSLOG, mx_itoa(widget_height));
//     // //mx_log_info(SYSLOG, (char*)filename);

//     GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(filename, widget_width, widget_height, NULL);

//     gtk_widget_set_size_request(widget_to_shrink, widget_width, widget_height);  
//     gtk_image_set_from_pixbuf(image, pixbuf);
// }

void mx_set_image_limit_size(GtkImage* image, GtkWidget* widget_to_shrink, const char* filename) {
    GdkPixbuf *given_image = gdk_pixbuf_new_from_file(filename, NULL);
    int widget_width;
    int widget_height;

    int image_width = gdk_pixbuf_get_width(given_image);
    int image_height = gdk_pixbuf_get_height(given_image); 

    float width_ratio;
    float height_ratio;
    float max_ratio;

    gtk_widget_get_size_request(widget_to_shrink, &widget_width, &widget_height);

    width_ratio = image_width / widget_width;
    height_ratio = image_height / widget_height;
    
    if (width_ratio > height_ratio)
        max_ratio = width_ratio;
    else
        max_ratio = height_ratio;
    
    if (max_ratio > 1) {
        image_height /= max_ratio;
        image_width /= max_ratio;
    }

    // //mx_log_info(SYSLOG, "Image info: width, height, path vvv" );
    // //mx_log_info(SYSLOG, mx_itoa(widget_width));
    // //mx_log_info(SYSLOG, mx_itoa(widget_height));
    // //mx_log_info(SYSLOG, mx_itoa(image_width));
    // //mx_log_info(SYSLOG, mx_itoa(image_height));
    // //mx_log_info(SYSLOG, (char*)filename);

    GdkPixbuf *new_image = gdk_pixbuf_new_from_file_at_size(filename, image_width, image_height, NULL);

    gtk_widget_set_size_request(widget_to_shrink, image_width, image_height);    
    gtk_image_set_from_pixbuf(image, new_image);
}

void mx_set_style(GtkWidget *widget) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, RESOURCE_CSS_MAIN_PATH, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void mx_add_css_class(GtkWidget *widget, const char *classname) {
    GtkStyleContext *context;
    context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, classname);
}
