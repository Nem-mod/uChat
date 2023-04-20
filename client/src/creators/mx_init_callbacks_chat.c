#include "client.h"

void mx_init_callbacks_chat(t_uchat_application* app) {
    // g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->chat_scene->w_chat, "destroy", G_CALLBACK (mx_clear_app), app);
    g_signal_connect(app->scenes->chat_scene->b_add_contact, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->add_contact_dwindow->cbdata);
    g_signal_connect(app->scenes->chat_scene->b_send_message, "clicked", G_CALLBACK (mx_callback_send_message), app);
    g_signal_connect(app->scenes->chat_scene->b_send_message, "clicked", G_CALLBACK (mx_callback_send_message), app);
    g_signal_connect(app->scenes->chat_scene->bc_file, "file-set", G_CALLBACK(mx_callback_choose_file), app);

}

