#include "client.h"

void mx_init_callbacks_add_contact(t_uchat_application* app) {
    g_signal_connect(app->scenes->add_contact_dwindow->w_add_contact , "delete-event", G_CALLBACK (mx_callback_on_delete_event), app->scenes->add_contact_dwindow->w_add_contact);
    g_signal_connect(app->scenes->add_contact_dwindow->b_close , "clicked", G_CALLBACK (mx_callback_hide_window), app);
    g_signal_connect(app->scenes->add_contact_dwindow->b_add_contact, "clicked", G_CALLBACK(mx_callback_add_contact), app);
    //g_signal_connect(app->scenes->add_contact_dwindow->b_add_contact, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->add_contact_dwindow->cbdata);
}

void mx_callback_hide_window_crt(UNUSED GtkButton *button, gpointer data) {
    t_uchat_application *app = (t_uchat_application*)data; 

    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
}

void mx_init_create_group(t_uchat_application* app) {
    g_signal_connect(app->scenes->create_group_dwindow->w_create_group , "delete-event", G_CALLBACK (mx_callback_on_delete_event), app->scenes->create_group_dwindow->w_create_group);
    g_signal_connect(app->scenes->create_group_dwindow->b_close , "clicked", G_CALLBACK (mx_callback_hide_window_crt), app);
    g_signal_connect(app->scenes->create_group_dwindow->b_create_group, "clicked", G_CALLBACK(mx_callback_create_group), app);
}

void mx_init_callbacks_chat(t_uchat_application* app) {
    // g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->chat_scene->w_chat, "destroy", G_CALLBACK (mx_clear_app), app);
    g_signal_connect(app->scenes->chat_scene->b_add_contact, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->add_contact_dwindow->cbdata);
    g_signal_connect(app->scenes->chat_scene->b_add_group, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->create_group_dwindow->cbdata);
    g_signal_connect(app->scenes->chat_scene->b_profile, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->user_profile_dwindow->cbdata);

    g_signal_connect(app->scenes->chat_scene->b_send_message, "clicked", G_CALLBACK (mx_callback_send_message), app);
    g_signal_connect(app->scenes->chat_scene->e_f_chat, "activate", G_CALLBACK(mx_callback_send_message), app);
    g_signal_connect(app->scenes->chat_scene->bc_file, "file-set", G_CALLBACK(mx_callback_choose_file), app);

}

void mx_init_callbacks_signin(t_uchat_application* app) {
    g_signal_connect(app->scenes->signin_scene->b_signin, "clicked", G_CALLBACK (mx_callback_auth), app);
    // g_signal_connect(app->scenes->signin_scene->b_signin, "activate", G_CALLBACK (mx_callback_test), app);
    g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signup_scene->cbdata);
    g_signal_connect(app->scenes->signin_scene->w_signin, "destroy", G_CALLBACK (mx_clear_app), app);
}

void mx_init_callbacks_signup(t_uchat_application* app) {
    g_signal_connect(app->scenes->signup_scene->b_signup, "clicked", G_CALLBACK (mx_callback_registration), app);
    // g_signal_connect(app->scenes->signup_scene, "activate", G_CALLBACK (mx_callback_test), app);
    g_signal_connect(app->scenes->signup_scene->bl_signin, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->signup_scene->w_signup, "destroy", G_CALLBACK (mx_clear_app), app);
}

void mx_init_user_profile(t_uchat_application* app) {
    g_signal_connect(app->scenes->user_profile_dwindow->wd_user_profile , "delete-event", G_CALLBACK (mx_callback_on_delete_event), app->scenes->user_profile_dwindow->wd_user_profile);
    g_signal_connect(app->scenes->user_profile_dwindow->b_logout, "clicked", G_CALLBACK(mx_callback_log_out), app);
    g_signal_connect(app->scenes->user_profile_dwindow->b_confirm, "clicked", G_CALLBACK(mx_callback_patch_user), app);
    g_signal_connect(app->scenes->user_profile_dwindow->bc_file, "file-set", G_CALLBACK(mx_callback_choose_file), app);
    g_signal_connect(app->scenes->user_profile_dwindow->bc_file, "file-set", G_CALLBACK(mx_callback_set_up_profile_image), app);
}

