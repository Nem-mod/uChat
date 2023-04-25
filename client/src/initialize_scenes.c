#include "client.h"

void mx_init_scene_add_contact(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_ADD_CONT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        //mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->add_contact_dwindow = malloc(sizeof(t_add_contact_scene));

    *new_scene = ADD_CONTACT;
    app->scenes->add_contact_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->add_contact_dwindow->w_add_contact= mx_get_widget(builder, "addcontact_window");
    //app->scenes->signin_scene->gr_signin = mx_get_widget(builder, "login_grid");
    app->scenes->add_contact_dwindow->e_f_login = mx_get_widget(builder, "login_entry_contact");
    app->scenes->add_contact_dwindow->b_add_contact = mx_get_widget(builder, "add_contact_button");
    app->scenes->add_contact_dwindow->b_close = mx_get_widget(builder, "cancel_button");
    app->scenes->add_contact_dwindow->l_add_contact = mx_get_widget(builder, "add_contact_label");

    mx_set_style(app->scenes->add_contact_dwindow->w_add_contact);
    mx_set_style(app->scenes->add_contact_dwindow->l_add_contact);
    mx_set_style(app->scenes->add_contact_dwindow->e_f_login);
    mx_set_style(app->scenes->add_contact_dwindow->b_add_contact);
    mx_set_style(app->scenes->add_contact_dwindow->b_close);
    mx_add_css_class(app->scenes->add_contact_dwindow->l_add_contact, "add-label");
    mx_add_css_class(app->scenes->add_contact_dwindow->b_add_contact, "button2");
    mx_add_css_class(app->scenes->add_contact_dwindow->b_close, "button2");
    mx_add_css_class(app->scenes->add_contact_dwindow->w_add_contact, "background");

    //gtk_widget_set_visible(app->scenes->signin_scene->gr_signin, TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->add_contact_dwindow->w_add_contact), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->add_contact_dwindow->w_add_contact);
}

void mx_init_scene_chat(t_uchat_application* app){
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        //mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->chat_scene = malloc(sizeof(t_chat_scene));

    *new_scene = CHAT;
    app->scenes->chat_scene->cbdata = mx_create_callback_data(app, new_scene);
    
    app->scenes->chat_scene->w_chat = mx_get_widget(builder, "chat_window");

    app->scenes->chat_scene->chat_cat1 = mx_get_widget(builder, "chat_cat1");

    app->scenes->chat_scene->e_f_chats = mx_get_widget(builder, "chats_entry");
    app->scenes->chat_scene->w_sc_chats = mx_get_widget(builder, "chats_sc_window");
    app->scenes->chat_scene->v_sc_chats = mx_get_widget(builder, "chats_viewport");
    app->scenes->chat_scene->l_sc_chats = mx_get_widget(builder, "chats_list");
    app->scenes->chat_scene->b_add_contact = mx_get_widget(builder, "add_contact_button");
    app->scenes->chat_scene->b_add_group = mx_get_widget(builder, "add_group_button");

    app->scenes->chat_scene->img_chat = mx_get_widget(builder, "chat_image");
    app->scenes->chat_scene->l_chatname = mx_get_widget(builder, "chat_name_label");
    app->scenes->chat_scene->w_sc_messages = mx_get_widget(builder, "messages_sc_window");
    app->scenes->chat_scene->v_sc_messages = mx_get_widget(builder, "messages_viewport");
    app->scenes->chat_scene->l_sc_messages = mx_get_widget(builder, "messages_list");
    app->scenes->chat_scene->bc_file = mx_get_widget(builder, "file_choose_button");
    
    app->scenes->chat_scene->e_f_chat = mx_get_widget(builder, "chat_send_entry");
    app->scenes->chat_scene->b_send_message = mx_get_widget(builder, "message_send_button");
    app->scenes->chat_scene->b_chat_settings = mx_get_widget(builder, "edit_chat_button");

    app->scenes->chat_scene->img_user = mx_get_widget(builder, "user_image");
    app->scenes->chat_scene->b_profile = mx_get_widget(builder, "profile_button");

    // app->scenes->chat_scene->s_separator1 = mx_get_widget(builder, "separator1");
    // app->scenes->chat_scene->s_separator2 = mx_get_widget(builder, "separator2");
    // app->scenes->chat_scene->s_separator3 = mx_get_widget(builder, "separator3");
    
    // mx_add_css_class(app->scenes->chat_scene->s_separator1, "background");
    // mx_add_css_class(app->scenes->chat_scene->s_separator2, "background");
    // mx_add_css_class(app->scenes->chat_scene->s_separator3, "background");
    mx_add_css_class(app->scenes->chat_scene->w_sc_chats, "background");
    mx_add_css_class(app->scenes->chat_scene->w_sc_messages, "background");
    //mx_add_css_class(app->scenes->chat_scene->img_chat, "contact-img");
    //mx_add_css_class(app->scenes->chat_scene->img_user, "contact-img");


    mx_add_css_class(app->scenes->chat_scene->b_chat_settings, "button3");
    mx_add_css_class(app->scenes->chat_scene->b_add_contact, "button2");
    mx_add_css_class(app->scenes->chat_scene->b_add_group, "button2");
    mx_add_css_class(app->scenes->chat_scene->b_send_message, "button3");
    mx_add_css_class(app->scenes->chat_scene->bc_file, "button1");
    mx_add_css_class(app->scenes->chat_scene->b_profile, "button3");
    mx_add_css_class(app->scenes->chat_scene->w_chat, "background");
    mx_add_css_class(app->scenes->chat_scene->l_sc_chats, "background");
    //mx_add_css_class(app->scenes->chat_scene->v_sc_chats, "background");
    mx_add_css_class(app->scenes->chat_scene->l_sc_messages, "background-light");

    //mx_set_style(app->scenes->chat_scene->img_user);
    //mx_set_style(app->scenes->chat_scene->img_chat);
    mx_set_style(app->scenes->chat_scene->w_sc_messages);
    mx_set_style(app->scenes->chat_scene->w_sc_chats);
    mx_set_style(app->scenes->chat_scene->w_chat);
    mx_set_style(app->scenes->chat_scene->l_sc_messages); 
    mx_set_style(app->scenes->chat_scene->l_sc_chats);
    mx_set_style(app->scenes->chat_scene->e_f_chats);
    mx_set_style(app->scenes->chat_scene->b_add_contact);
    mx_set_style(app->scenes->chat_scene->b_add_group);
    mx_set_style(app->scenes->chat_scene->w_chat);
    //mx_set_style(path, app->scenes->chat_scene->m_box);
    mx_set_style(app->scenes->chat_scene->l_sc_chats);
    mx_set_style(app->scenes->chat_scene->e_f_chat);
    mx_set_style(app->scenes->chat_scene->b_send_message);
    mx_set_style(app->scenes->chat_scene->bc_file);
    mx_set_style(app->scenes->chat_scene->b_profile);
    mx_set_style(app->scenes->chat_scene->b_chat_settings);

    // mx_set_style(app->scenes->chat_scene->s_separator1);
    // mx_set_style(app->scenes->chat_scene->s_separator2);
    // mx_set_style(app->scenes->chat_scene->s_separator3);
    
    GtkWidget* add_contact_icon = mx_get_widget(builder, "add_contact_icon");
    GtkWidget* add_group_icon = mx_get_widget(builder, "add_group_icon");

    mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->chat_cat1), app->scenes->chat_scene->chat_cat1, RESOURCE_HEARTS_CAT_PATH);
    
    mx_set_image_widget_size(GTK_IMAGE(add_contact_icon), add_contact_icon ,mx_strjoin(RESOURCE_ICONS_PATH, "add-user.png"));
    mx_set_image_widget_size(GTK_IMAGE(add_group_icon), add_group_icon ,mx_strjoin(RESOURCE_ICONS_PATH, "add-group.png"));
    gtk_widget_hide(app->scenes->chat_scene->b_chat_settings);
    gtk_widget_hide(app->scenes->chat_scene->w_chat);
    g_object_unref(builder);
}

void mx_init_scene_create_group(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CREATE_GROUP_PATH, &error) == 0) {
        //mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->create_group_dwindow = malloc(sizeof(t_create_group_scene));

    *new_scene = CREATE_GROUP;
    app->scenes->create_group_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->create_group_dwindow->w_create_group = mx_get_widget(builder, "create_group_window");
    app->scenes->create_group_dwindow->e_f_group_name = mx_get_widget(builder, "group_name_entry_contact");
    app->scenes->create_group_dwindow->b_create_group = mx_get_widget(builder, "add_group_button");
    app->scenes->create_group_dwindow->b_close = mx_get_widget(builder, "cancel_button");
    app->scenes->create_group_dwindow->l_create_group = mx_get_widget(builder, "create_group_label");

    mx_set_style(app->scenes->create_group_dwindow->w_create_group);
    mx_set_style(app->scenes->create_group_dwindow->e_f_group_name);
    mx_set_style(app->scenes->create_group_dwindow->b_create_group);
    mx_set_style(app->scenes->create_group_dwindow->b_close);
    mx_set_style(app->scenes->create_group_dwindow->l_create_group);

    mx_add_css_class(app->scenes->create_group_dwindow->b_create_group, "button2");
    mx_add_css_class(app->scenes->create_group_dwindow->b_close, "button2");
    mx_add_css_class(app->scenes->create_group_dwindow->l_create_group, "add-label");


    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->create_group_dwindow->w_create_group), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->create_group_dwindow->w_create_group);
}

void mx_init_scene_signin(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_SIGNIN_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        //mx_log_err(SYSLOG, "gtk: Error loading file");
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
    app->scenes->signin_scene->l_signin = mx_get_widget(builder, "signin_label");
    app->scenes->signin_scene->l_welcome = mx_get_widget(builder, "welcome_label");

    app->scenes->signin_scene->img_paw1 = mx_get_widget(builder, "paw_image_signin1");
    app->scenes->signin_scene->img_paw2 = mx_get_widget(builder, "paw_image_signin2");
    //gtk_widget_set_visible(app->scenes->signin_scene->gr_signin, TRUE);

    mx_add_css_class(app->scenes->signin_scene->b_signin, "button1");
    mx_add_css_class(app->scenes->signin_scene->l_signin, "sign-label");
    mx_add_css_class(app->scenes->signin_scene->l_welcome, "welcome-label");

    mx_set_style(app->scenes->signin_scene->e_f_login);
    mx_set_style(app->scenes->signin_scene->e_f_password);
    mx_set_style(app->scenes->signin_scene->b_signin);
    mx_set_style(app->scenes->signin_scene->l_err_msg);
    mx_set_style(app->scenes->signin_scene->bl_signup);
    mx_set_style(app->scenes->signin_scene->w_signin);
    mx_set_style(app->scenes->signin_scene->l_signin);
    mx_set_style(app->scenes->signin_scene->l_welcome);

    mx_add_css_class(app->scenes->signin_scene->l_err_msg, "err-label");

    mx_set_image_widget_size(GTK_IMAGE(app->scenes->signin_scene->img_paw1), app->scenes->signin_scene->img_paw1, RESOURCE_PAW1_PATH);
    
    GdkPixbufAnimation *animation = gdk_pixbuf_animation_new_from_file(RESOURCE_DANCING_CAT1_PATH, NULL);
    gtk_image_set_from_animation(GTK_IMAGE(app->scenes->signin_scene->img_paw2), animation);

    gtk_widget_hide(app->scenes->signin_scene->w_signin);
    g_object_unref(builder);
}

void mx_init_scene_signup(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;


    if (gtk_builder_add_from_file(builder, RESOURCE_SIGNUP_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        //mx_log_err(SYSLOG, "gtk: Error loading file");
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
    app->scenes->signup_scene->l_signup = mx_get_widget(builder, "signup_label");
    app->scenes->signup_scene->l_welcome = mx_get_widget(builder, "welcome1_label");

    app->scenes->signup_scene->img_paw1 = mx_get_widget(builder, "paw_image_signup1");


    mx_add_css_class(app->scenes->signup_scene->l_signup, "sign-label");
    mx_add_css_class(app->scenes->signup_scene->l_welcome, "welcome-label");
    mx_add_css_class(app->scenes->signup_scene->b_signup, "button1");

    mx_set_style(app->scenes->signup_scene->w_signup);
    mx_set_style(app->scenes->signup_scene->e_f_login);
    mx_set_style(app->scenes->signup_scene->e_f_password);
    mx_set_style(app->scenes->signup_scene->e_f_password2);
    mx_set_style(app->scenes->signup_scene->e_f_firstName);
    mx_set_style(app->scenes->signup_scene->e_f_lastName);
    mx_set_style(app->scenes->signup_scene->b_signup);
    mx_set_style(app->scenes->signup_scene->l_signup);
    mx_set_style(app->scenes->signup_scene->l_welcome);
    mx_set_style(app->scenes->signup_scene->l_first_name_err);
    mx_set_style(app->scenes->signup_scene->l_second_name_err);
    mx_set_style(app->scenes->signup_scene->l_login_err);
    mx_set_style(app->scenes->signup_scene->l_password_err);
    mx_set_style(app->scenes->signup_scene->l_repeat_password_err);

    mx_add_css_class(app->scenes->signup_scene->l_first_name_err, "err-label");
    mx_add_css_class(app->scenes->signup_scene->l_second_name_err, "err-label");
    mx_add_css_class(app->scenes->signup_scene->l_login_err, "err-label");
    mx_add_css_class(app->scenes->signup_scene->l_password_err, "err-label");
    mx_add_css_class(app->scenes->signup_scene->l_repeat_password_err, "err-label");

    mx_set_image_widget_size(GTK_IMAGE(app->scenes->signup_scene->img_paw1), app->scenes->signup_scene->img_paw1, RESOURCE_SLEEPING_CAT2_PATH);

    gtk_widget_hide(app->scenes->signup_scene->w_signup);
    g_object_unref(builder);
}

void mx_init_scene_user_profile(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_PROFILE_WINDOW_PATH, &error) == 0) {
        //mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->user_profile_dwindow = malloc(sizeof(t_user_profile_scene));

    *new_scene = PROFILE;
    app->scenes->user_profile_dwindow->cbdata = mx_create_callback_data(app, new_scene);
        
    app->scenes->user_profile_dwindow->w_user_profile = mx_get_widget(builder, "profile_window");
    app->scenes->user_profile_dwindow->l_profile = mx_get_widget(builder, "profile_label");
    app->scenes->user_profile_dwindow->l_login = mx_get_widget(builder, "login_word_label");
    app->scenes->user_profile_dwindow->l_user_login = mx_get_widget(builder, "login_label");
    app->scenes->user_profile_dwindow->img_user = mx_get_widget(builder, "user_image");
    app->scenes->user_profile_dwindow->bc_file = mx_get_widget(builder, "change_user_image");
    app->scenes->user_profile_dwindow->b_logout = mx_get_widget(builder, "logout_button");
    app->scenes->user_profile_dwindow->b_confirm = mx_get_widget(builder, "confirm_changes_button");
    app->scenes->user_profile_dwindow->b_cancel = mx_get_widget(builder, "cancel_button");
    
    mx_add_css_class(app->scenes->user_profile_dwindow->l_user_login, "for-names-label");
    mx_add_css_class(app->scenes->user_profile_dwindow->l_login, "usual-label");
    mx_add_css_class(app->scenes->user_profile_dwindow->l_profile, "add-label");
    mx_add_css_class(app->scenes->user_profile_dwindow->b_cancel, "button2");
    mx_add_css_class(app->scenes->user_profile_dwindow->bc_file, "button1");
    mx_add_css_class(app->scenes->user_profile_dwindow->b_confirm, "button2");
    mx_add_css_class(app->scenes->user_profile_dwindow->b_logout, "button2");
    mx_add_css_class(app->scenes->user_profile_dwindow->w_user_profile, "background");

    mx_set_style(app->scenes->user_profile_dwindow->l_login);
    mx_set_style(app->scenes->user_profile_dwindow->l_user_login);
    mx_set_style(app->scenes->user_profile_dwindow->l_profile);
    mx_set_style(app->scenes->user_profile_dwindow->b_cancel);
    mx_set_style(app->scenes->user_profile_dwindow->w_user_profile);
    mx_set_style(app->scenes->user_profile_dwindow->bc_file);
    mx_set_style(app->scenes->user_profile_dwindow->b_confirm);
    mx_set_style(app->scenes->user_profile_dwindow->b_logout);

    
    GtkWidget* log_out_icon = mx_get_widget(builder, "log_out_icon");
    mx_set_image_widget_size(GTK_IMAGE(log_out_icon), log_out_icon, mx_strjoin(RESOURCE_ICONS_PATH, "log-out.png"));
    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->user_profile_dwindow->w_user_profile), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->user_profile_dwindow->w_user_profile);
}

void mx_init_scene_group_info(t_uchat_application* app) {
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;


    if (gtk_builder_add_from_file(builder, RESOURCE_GROUP_INFO_PATH, &error) == 0) {
        //mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    t_SCENE *new_scene = malloc(sizeof(t_SCENE));
    app->scenes->group_info_dwindow = malloc(sizeof(t_group_info_scene));

    *new_scene = GROUP_INFO;
    app->scenes->group_info_dwindow->cbdata = mx_create_callback_data(app, new_scene);

    app->scenes->group_info_dwindow->w_group_info = mx_get_widget(builder, "group_info_window");
    app->scenes->group_info_dwindow->l_group_info = mx_get_widget(builder, "group_info_label");
    app->scenes->group_info_dwindow->e_f_new_group_member = mx_get_widget(builder, "group_user_entry");
    app->scenes->group_info_dwindow->b_add_member = mx_get_widget(builder, "add_user_togroup_button");
    app->scenes->group_info_dwindow->b_close = mx_get_widget(builder, "close_button");

    app->scenes->group_info_dwindow->w_sc_members = mx_get_widget(builder, "group_edit_cs_window");
    app->scenes->group_info_dwindow->v_sc_members = mx_get_widget(builder, "group_edit_add_viewport");
    app->scenes->group_info_dwindow->l_sc_members = mx_get_widget(builder, "user_list");

    app->scenes->group_info_dwindow->img_group = mx_get_widget(builder, "group_image");
    app->scenes->group_info_dwindow->e_f_new_group_name = mx_get_widget(builder, "group_name_entry");
    app->scenes->group_info_dwindow->b_confirm = mx_get_widget(builder, "name_group_confirm_button");
    app->scenes->group_info_dwindow->bc_file = mx_get_widget(builder, "group_image_change_button");

    mx_add_css_class(app->scenes->group_info_dwindow->w_group_info, "background");
    mx_add_css_class(app->scenes->group_info_dwindow->b_add_member, "button2");
    mx_add_css_class(app->scenes->group_info_dwindow->b_close, "button2");
    mx_add_css_class(app->scenes->group_info_dwindow->b_confirm, "button2");
    mx_add_css_class(app->scenes->group_info_dwindow->l_group_info, "add-label");
    mx_add_css_class(app->scenes->group_info_dwindow->bc_file, "button1");

    mx_set_style(app->scenes->group_info_dwindow->w_group_info);
    mx_set_style(app->scenes->group_info_dwindow->l_group_info);
    mx_set_style(app->scenes->group_info_dwindow->b_add_member);
    mx_set_style(app->scenes->group_info_dwindow->b_close);
    mx_set_style(app->scenes->group_info_dwindow->b_confirm);
    mx_set_style(app->scenes->group_info_dwindow->b_confirm);
    mx_set_style(app->scenes->group_info_dwindow->e_f_new_group_name);
    mx_set_style(app->scenes->group_info_dwindow->e_f_new_group_member);
    mx_set_style(app->scenes->group_info_dwindow->bc_file);


    gtk_window_set_transient_for(GTK_WINDOW(app->scenes->group_info_dwindow->w_group_info), GTK_WINDOW(app->scenes->chat_scene->w_chat));
    gtk_widget_hide(app->scenes->group_info_dwindow->w_group_info);
    g_object_unref(builder);
}
