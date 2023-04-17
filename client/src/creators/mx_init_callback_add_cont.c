#include "client.h"


void mx_init_add_cont(t_uchat_application* app) {
    // g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->add_contact_dwindow->b_close , "clicked", G_CALLBACK (mx_hide_window), app);

    //g_signal_connect(app->scenes->add_contact_dwindow->b_add_contact, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->add_contact_dwindow->cbdata);
}
