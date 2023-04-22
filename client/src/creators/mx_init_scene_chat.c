#include "client.h"

void mx_init_scene_chat(t_uchat_application* app){
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    const gchar *path = "client/Resources/css/main.css";
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

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
    app->scenes->chat_scene->b_add_contact = mx_get_widget(builder, "add_contact_button");
    app->scenes->chat_scene->b_add_group = mx_get_widget(builder, "add_group_button");

    app->scenes->chat_scene->img_chat = mx_get_widget(builder, "chat_image");
    app->scenes->chat_scene->l_chatname = mx_get_widget(builder, "chat_name_label");
    app->scenes->chat_scene->b_chat_profile = mx_get_widget(builder, "chat_profile_button");
    app->scenes->chat_scene->w_sc_messages = mx_get_widget(builder, "messages_sc_window");
    app->scenes->chat_scene->v_sc_messages = mx_get_widget(builder, "messages_viewport");
    app->scenes->chat_scene->l_sc_messages = mx_get_widget(builder, "messages_list");
    
    app->scenes->chat_scene->e_f_file = mx_get_widget(builder, "file_entry");
    app->scenes->chat_scene->e_f_chat = mx_get_widget(builder, "chat_send_entry");
    app->scenes->chat_scene->b_send_message = mx_get_widget(builder, "message_send_button");

    gtk_widget_set_name(app->scenes->chat_scene->w_chat, "chat_window");

    printf("Window name(id): \"%s\"\n", gtk_widget_get_name(app->scenes->chat_scene->w_chat));

    mx_set_style(path, app->scenes->chat_scene->e_f_chats);
    mx_set_style(path, app->scenes->chat_scene->b_add_contact);
    mx_set_style(path, app->scenes->chat_scene->b_add_group);
    mx_set_style(path, app->scenes->chat_scene->e_f_file);
    mx_set_style(path, app->scenes->chat_scene->b_chat_profile);

    mx_set_style(path, app->scenes->chat_scene->e_f_chat);
    mx_set_style(path, app->scenes->chat_scene->b_send_message);
    mx_set_style(path, app->scenes->chat_scene->w_chat);
    
    gtk_widget_hide(app->scenes->chat_scene->w_chat);
    g_object_unref(builder);
}
