#include "client.h"

void mx_init_scene_add_contact(t_uchat_application* app) {
    if(app){}
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    const gchar *path = "client/Resources/css/addcontact.css";
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_ADD_CONT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->add_contact_dwindow = malloc(sizeof(t_add_contact));

    *new_scene = ADD_CONTACT;
    app->scenes->add_contact_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->add_contact_dwindow->w_add_contact= mx_get_widget(builder, "addcontact_window");
    //app->scenes->signin_scene->gr_signin = mx_get_widget(builder, "login_grid");
    app->scenes->add_contact_dwindow->e_f_login = mx_get_widget(builder, "login_entry_contact");
    app->scenes->add_contact_dwindow->b_add_contact = mx_get_widget(builder, "add_contact_button");
    app->scenes->add_contact_dwindow->b_close = mx_get_widget(builder, "cancel_button");

    mx_set_style(path, app->scenes->add_contact_dwindow->e_f_login);
    mx_set_style(path, app->scenes->add_contact_dwindow->b_add_contact);
    mx_set_style(path, app->scenes->add_contact_dwindow->b_close);

    //gtk_widget_set_visible(app->scenes->signin_scene->gr_signin, TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->add_contact_dwindow->w_add_contact), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
}

void mx_init_scene_chat(t_uchat_application* app){
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    const gchar *path = "client/Resources/css/chat.css";
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
    app->scenes->chat_scene->bc_file = mx_get_widget(builder, "file_choose_button");
    
    app->scenes->chat_scene->e_f_file = mx_get_widget(builder, "file_entry");
    app->scenes->chat_scene->e_f_chat = mx_get_widget(builder, "chat_send_entry");
    app->scenes->chat_scene->b_send_message = mx_get_widget(builder, "message_send_button");
    app->scenes->chat_scene->b_chat_settings = mx_get_widget(builder, "edit_chat_button");

    app->scenes->chat_scene->img_user = mx_get_widget(builder, "user_image");
    app->scenes->chat_scene->b_profile =  mx_get_widget(builder, "profile_button");

    mx_set_style(path, app->scenes->chat_scene->e_f_chats);
    mx_set_style(path, app->scenes->chat_scene->b_add_contact);
    mx_set_style(path, app->scenes->chat_scene->b_add_group);
    mx_set_style(path, app->scenes->chat_scene->e_f_file);
    mx_set_style(path, app->scenes->chat_scene->b_chat_profile);

    mx_set_style(path, app->scenes->chat_scene->e_f_chat);
    mx_set_style(path, app->scenes->chat_scene->b_send_message);
    
    GtkWidget* add_contact_icon =mx_get_widget(builder, "add_contact_icon");
    GtkWidget* add_group_icon =mx_get_widget(builder, "add_group_icon");
    gtk_image_set_from_file(GTK_IMAGE(add_contact_icon), mx_strjoin(RESOURCE_ICONS_PATH, "add-user.png"));
    gtk_image_set_from_file(GTK_IMAGE(add_group_icon), mx_strjoin(RESOURCE_ICONS_PATH, "add-group.png"));
    gtk_widget_hide(app->scenes->chat_scene->w_chat);
    g_object_unref(builder);
}

void mx_init_scene_create_group(t_uchat_application* app) {
    if(app){}
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CREATE_GROUP_PATH, &error) == 0) {
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->create_group_dwindow = malloc(sizeof(t_create_group));

    *new_scene = CREATE_GROUP;
    app->scenes->create_group_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->create_group_dwindow->w_create_group = mx_get_widget(builder, "create_group_window");
    app->scenes->create_group_dwindow->e_f_group_name = mx_get_widget(builder, "group_name_entry_contact");
    app->scenes->create_group_dwindow->b_create_group = mx_get_widget(builder, "add_group_button");
    app->scenes->create_group_dwindow->b_close = mx_get_widget(builder, "cancel_button");
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->create_group_dwindow->w_create_group), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
}

void mx_init_scene_signin(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    const gchar *path = "client/Resources/css/signin.css";
    // const gchar *path = "client/Resources/css/gtk.css";
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_SIGNIN_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->signin_scene = malloc(sizeof(t_signin_scene));

    *new_scene = SIGNIN;
    app->scenes->signin_scene->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->signin_scene->w_signin = mx_get_widget(builder, "signin_window");
    //app->scenes->signin_scene->gr_signin = mx_get_widget(builder, "login_grid");
    app->scenes->signin_scene->e_f_login = mx_get_widget(builder, "login_entry1");
    app->scenes->signin_scene->e_f_password = mx_get_widget(builder, "password_entry1");
    app->scenes->signin_scene->b_signin = mx_get_widget(builder, "signin_button");
    app->scenes->signin_scene->bl_signup = mx_get_widget(builder, "signin_link1");
    app->scenes->signin_scene->l_err_msg = mx_get_widget(builder, "err_msg");
    //gtk_widget_set_visible(app->scenes->signin_scene->gr_signin, TRUE);

    mx_set_style(path, app->scenes->signin_scene->e_f_login);
    mx_set_style(path, app->scenes->signin_scene->e_f_password);
    mx_set_style(path, app->scenes->signin_scene->b_signin);
    mx_set_style(path, app->scenes->signin_scene->l_err_msg);
    mx_set_style(path, app->scenes->signin_scene->bl_signup);
    mx_set_style(path, app->scenes->signin_scene->w_signin);

    
    gtk_widget_hide(app->scenes->signin_scene->w_signin);
    g_object_unref(builder);
}

void mx_init_scene_signup(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;
    const gchar *path = "client/Resources/css/signup.css";


    if (gtk_builder_add_from_file(builder, RESOURCE_SIGNUP_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->signup_scene = malloc(sizeof(t_signup_scene));

    *new_scene = SIGNUP;
    app->scenes->signup_scene->cbdata = mx_create_callback_data(app, new_scene);

    app->scenes->signup_scene->w_signup = mx_get_widget(builder, "signup_window");
    app->scenes->signup_scene->e_f_login = mx_get_widget(builder, "login_entry");
    app->scenes->signup_scene->e_f_password = mx_get_widget(builder, "password_entry");
    app->scenes->signup_scene->e_f_password2 = mx_get_widget(builder, "r_password_entry");
    app->scenes->signup_scene->e_f_firstName = mx_get_widget(builder, "fname_entry");
    app->scenes->signup_scene->e_f_lastName = mx_get_widget(builder, "lname_entry");
    app->scenes->signup_scene->b_signup = mx_get_widget(builder, "register_button");
    app->scenes->signup_scene->bl_signin = mx_get_widget(builder, "signin_link");

    app->scenes->signup_scene->l_first_name_err = mx_get_widget(builder, "first_name_err");
    app->scenes->signup_scene->l_second_name_err = mx_get_widget(builder, "last_name_err");
    app->scenes->signup_scene->l_login_err = mx_get_widget(builder, "login_err");
    app->scenes->signup_scene->l_password_err = mx_get_widget(builder, "password_err");
    app->scenes->signup_scene->l_repeat_password_err = mx_get_widget(builder, "repeat_password_err");

    mx_set_style(path, app->scenes->signup_scene->w_signup);
    mx_set_style(path, app->scenes->signup_scene->e_f_login);
    mx_set_style(path, app->scenes->signup_scene->e_f_password);
    mx_set_style(path, app->scenes->signup_scene->e_f_password2);
    mx_set_style(path, app->scenes->signup_scene->e_f_firstName);
    mx_set_style(path, app->scenes->signup_scene->e_f_lastName);
    mx_set_style(path, app->scenes->signup_scene->b_signup);

    mx_set_style(path, app->scenes->signup_scene->l_first_name_err);
    mx_set_style(path, app->scenes->signup_scene->l_second_name_err);
    mx_set_style(path, app->scenes->signup_scene->l_login_err);
    mx_set_style(path, app->scenes->signup_scene->l_password_err);
    mx_set_style(path, app->scenes->signup_scene->l_repeat_password_err);

    gtk_widget_hide(app->scenes->signup_scene->w_signup);
    g_object_unref(builder);
}

void mx_init_scene_user_profile(t_uchat_application* app) {
    if(app){}
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_PROFILE_WINDOW_PATH, &error) == 0) {
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->user_profile_dwindow = malloc(sizeof(t_user_profile));

    *new_scene = PROFILE;
    app->scenes->user_profile_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->user_profile_dwindow->wd_user_profile = mx_get_widget(builder, "profile_window");
    app->scenes->user_profile_dwindow->l_user_login = mx_get_widget(builder, "user_login");
    app->scenes->user_profile_dwindow->img_user = mx_get_widget(builder, "user_image");
    app->scenes->user_profile_dwindow->bc_file = mx_get_widget(builder, "change_user_image");
    app->scenes->user_profile_dwindow->b_logout = mx_get_widget(builder, "logout_button");
    app->scenes->user_profile_dwindow->b_confirm = mx_get_widget(builder, "confirm_changes_button");
    
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->user_profile_dwindow->wd_user_profile), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->user_profile_dwindow->wd_user_profile);
}
