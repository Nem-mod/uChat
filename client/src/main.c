#include "client.h"

int main(int argc, char* argv[])
{
    remove(SYSLOG);
    if(argc != 2){
        mx_log_info(SYSLOG, "usage: ./uchat [port]");
        return 0;
    }
    gtk_init(&argc, &argv);
    t_UchatApplication* app = mx_create_app(argv);
    gtk_widget_show(app->scenes->signUp_scene->w_signup);

    g_signal_connect (app->scenes->signUp_scene->b_signup, "clicked", G_CALLBACK (mx_registratinon_callback), app);
    gtk_main ();

    return 0;
}
