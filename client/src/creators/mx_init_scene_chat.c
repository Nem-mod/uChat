#include "client.h"

void mx_init_scene_chat(GtkBuilder *builder, t_uchat_application* app){
    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->chat_scene = malloc(sizeof(t_chat_scene));

    *new_scene = CHAT;
    app->scenes->chat_scene->cbdata = mx_create_callback_data(app, new_scene);
    
    app->scenes->chat_scene->w_chat = mx_get_widget(builder, "chat_window");
    app->scenes->chat_scene->m_box = mx_get_widget(builder, "main_chat_box");
    app->scenes->chat_scene->e_f_chats = mx_get_widget(builder, "chats_entry");
    app->scenes->chat_scene->w_sc_chats = mx_get_widget(builder, "chats_sc_window");
    app->scenes->chat_scene->v_sc_chats = mx_get_widget(builder, "chats_viewport");
    app->scenes->chat_scene->l_sc_chats = mx_get_widget(builder, "chats_list");
    


    app->scenes->chat_scene->w_sc_messages = mx_get_widget(builder, "messages_sc_window");
    app->scenes->chat_scene->v_sc_messages = mx_get_widget(builder, "messages_viewport");
    app->scenes->chat_scene->l_sc_messages = mx_get_widget(builder, "messages_list");
    
    app->scenes->chat_scene->e_f_chat = mx_get_widget(builder, "chat_send_entry");
    app->scenes->chat_scene->b_send_message = mx_get_widget(builder, "message_send_button");
    
    // g_signal_connect(app->scenes->signin_scene->bl_signup, "clicked", G_CALLBACK (mx_callback_change_scene), app->scenes->signin_scene->cbdata);
    g_signal_connect(app->scenes->chat_scene->w_chat, "destroy", G_CALLBACK (mx_clear_app), app);
    
    gtk_widget_hide(app->scenes->chat_scene->w_chat);
}
