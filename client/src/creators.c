#include "client.h"

t_uchat_application* mx_create_app(char* argv[]) {
    t_uchat_application* app = malloc(sizeof(t_uchat_application));

    app->choosed_file_pname = NULL;
    app->user_id = 0;
    app->current_group_id = 0;
    app->last_message_id = 0;
    app->is_admin = false;
    app->last_member_widget_index = 0;
    app->last_group_widget_index = 0;


    mx_create_scenes(app);
    mx_init_server_connection(app, argv[1], mx_atoi(argv[2]));

    return app;
}

t_callback_data* mx_create_callback_data(t_uchat_application* app, void* data) {
    t_callback_data* cbdata = malloc(sizeof(t_callback_data));

    cbdata->app = app;
    cbdata->data = data;
    
    return cbdata;
}

t_contact* mx_create_contact(char* name, char* icon_path, int size) {
    t_contact *contact = malloc(sizeof(t_contact));

    contact->name = name;
    contact->icon = mx_create_file(icon_path, size);

    return contact;
}

t_file* mx_create_file(char* path, int size) {
    t_file *file = malloc(sizeof(t_file));

    file->path = path;
    file->size = size;

    return file;
}

void mx_create_scenes(t_uchat_application* app) {
    app->scenes = malloc(sizeof(t_uchat_scenes));

    mx_init_scene_chat(app);
    mx_init_scene_signin(app);
    mx_init_scene_signup(app);
    mx_init_scene_add_contact(app);
    mx_init_scene_create_group(app);
    mx_init_scene_user_profile(app);
    mx_init_scene_group_info(app);

    mx_init_callbacks_chat(app);
    mx_init_callbacks_signin(app);
    mx_init_callbacks_signup(app);
    mx_init_callbacks_add_contact(app);
    mx_init_callbacks_create_group(app);
    mx_init_callbacks_user_profile(app);
    mx_init_callbacks_group_info(app);
}

t_user* mx_create_user(char* login, char* pw, int id, char* name, char* icon_path, int size) {
    t_user *user = malloc(sizeof(t_user));
    
    user->login = login;
    user->password = pw;
    user->id = id;
    user->user_info = mx_create_contact(name, icon_path, size);

    return user;
}

void mx_create_new_chat_widget(t_uchat_application* app, t_response* res) {
    bool is_exist;
    
    struct json_object* jobj = json_tokener_parse(res->property);
    if(res->property == NULL) 
        return;

    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    struct json_object *jgroup_privacy = json_object_object_get(jobj, "group_privacy"); 
    struct json_object *jname;
    char* file_name = NULL;

    if(mx_strstr(res->property, "group_name")) {
        jname = json_object_object_get(jobj, "group_name"); 

        if(mx_strstr(res->property, "file_name")) {
            struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
            file_name = mx_strjoin(RESOURCE_PATH, (char*)json_object_get_string(jfname));
        } 
        else
            file_name = RESOURCE_BASE_GROUP_ICON;
    }
    else {
        jname = json_object_object_get(jobj, "nick_name"); 

        if(mx_strstr(res->property, "file_name")) {
            struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
            file_name = mx_strjoin(RESOURCE_PATH, (char*)json_object_get_string(jfname));
        }    
        else
            file_name = RESOURCE_BASE_ICON;
    }

    GtkWidget *chat_button = NULL;
    GtkWidget *chat_box = NULL;
    GtkWidget *chat_img = NULL;
    GtkWidget *chat_name = NULL;
    int row_index = -1;
    
    chat_button = mx_check_widget_exist(app->scenes->chat_scene->l_sc_chats, json_object_get_string(jgroup_id), &row_index);
 
    if (chat_button != NULL) {        
        is_exist = true;
        GList *children = gtk_container_get_children(GTK_CONTAINER(chat_button));

        chat_box = children->data;
        children = gtk_container_get_children(GTK_CONTAINER(children->data));

        chat_img = children->data;
        children = g_list_next(children);

        chat_name = children->data;

        if (row_index < app->last_group_widget_index) {
           
            for (int i = app->last_group_widget_index; i < (int)g_list_length(gtk_container_get_children(GTK_CONTAINER(app->scenes->chat_scene->l_sc_chats))); i++) {
                if (mx_atoi(gtk_widget_get_name(mx_get_widget_from_list(app->scenes->chat_scene->l_sc_chats, i))) == app->current_group_id) {
                    app->current_group_id = 0;
                    mx_callback_hide_chatbox(NULL, app);
                    mx_callback_hide_window_group_info(NULL, app);
                }
                gtk_widget_destroy(GTK_WIDGET(gtk_list_box_get_row_at_index(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats), i)));
                // mx_log_info("test.txt", "delete row on index (first loop)");
                // mx_log_info("test.txt", mx_itoa(i));
            }
            app->last_group_widget_index = 0;
        }
        for (int i = app->last_group_widget_index; i < row_index; i++) {
            if (mx_atoi(gtk_widget_get_name(mx_get_widget_from_list(app->scenes->chat_scene->l_sc_chats, i))) == app->current_group_id) {
                app->current_group_id = 0;
                mx_callback_hide_chatbox(NULL, app);
                mx_callback_hide_window_group_info(NULL, app);
            }
            gtk_widget_destroy(GTK_WIDGET(gtk_list_box_get_row_at_index(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats), i)));
            // mx_log_info("test.txt", "delete row on index (second loop)");
            // mx_log_info("test.txt", mx_itoa(i));
        }      
    } else {     
        GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
        GError *error = NULL;

        if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
            //mx_log_err(SYSLOG, "gtk: Error loading file");
            return;
        }   
        is_exist = false;
        chat_button = mx_get_widget(builder, "chat_button");
        chat_box = mx_get_widget(builder, "chat_box");
        chat_img = mx_get_widget(builder, "chat_img");
        chat_name = mx_get_widget(builder, "chat_name");
    }
    app->last_group_widget_index++;

    gtk_label_set_text(GTK_LABEL(chat_name), (char*)json_object_get_string(jname));
    gtk_widget_set_name(chat_button,  json_object_get_string(jgroup_id));
    gtk_widget_set_name(chat_box, json_object_get_string(jgroup_privacy));
    gtk_widget_set_name(chat_name, "chat_name");

    mx_set_style(chat_button);
    mx_set_style(chat_box);
    mx_set_style(chat_name);
    mx_set_style(chat_img);

    mx_add_css_class(chat_button, "contact-background");
    mx_add_css_class(chat_box, "contact-background-inner");
    mx_add_css_class(chat_name, "contact-name");
    mx_add_css_class(chat_img, "contact-img");
    if (json_object_get_int(jgroup_id) == app->current_group_id) {
        gtk_label_set_text(GTK_LABEL(app->scenes->chat_scene->l_chatname), (char*)json_object_get_string(jname));
        mx_set_image_widget_size(GTK_IMAGE(app->scenes->chat_scene->img_chat), app->scenes->chat_scene->img_chat, file_name);
        gtk_widget_set_name(app->scenes->chat_scene->img_chat, file_name);
    }

    gtk_widget_set_name(chat_img, file_name);
    mx_set_image_widget_size(GTK_IMAGE(chat_img), chat_img, file_name);

    gtk_widget_set_size_request(chat_box, 10, 10);
    if (!is_exist) {                
        gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats), chat_button, -1);
        g_signal_connect(chat_button, "clicked", G_CALLBACK(mx_callback_show_chatbox), app);
        g_signal_connect(chat_button, "clicked", G_CALLBACK(mx_callback_chatbox), app);
    }
        
    //g_object_unref(builder);
}

void mx_create_new_member_widget(t_uchat_application* app, t_response* res) {
    bool is_exist;
    
    struct json_object* jobj = json_object_array_get_idx(json_tokener_parse(res->property), 0); // TODO: move this block on 153+ lines
    if(res->property == NULL) 
        return;

    struct json_object* juser_id = json_object_object_get(jobj, "user_id");
    struct json_object* juser_name = json_object_object_get(jobj, "nick_name");
    char* file_name = NULL;
    char* formatted_login = NULL;

    if(mx_strstr(res->property, "file_name")) {
        struct json_object *jfname = json_object_object_get(jobj, "file_name"); 
        file_name = mx_strjoin(RESOURCE_PATH, (char*)json_object_get_string(jfname));
    }    
    else
        file_name = RESOURCE_BASE_ICON;

    if (json_object_get_int(juser_id) == app->user_id)
        formatted_login = mx_strjoin(json_object_get_string(juser_name), " (You)");
    else
        formatted_login = (char*)json_object_get_string(juser_name);

    GtkWidget* first_member = mx_get_widget_from_list(app->scenes->group_info_dwindow->l_sc_members, 0);
    if (first_member == NULL || mx_strcmp(gtk_widget_get_name(first_member), json_object_get_string(juser_id)) == 0) {
        formatted_login = mx_strjoin(formatted_login, " (Admin)");
        if (json_object_get_int(juser_id) == app->user_id)
            app->is_admin = true;
    }

    GtkWidget* member_box = NULL;
    GtkWidget* img_member = NULL;
    GtkWidget* l_member_name = NULL;
    GtkWidget* b_delete = NULL;
    int row_index = -1;

    member_box = mx_check_widget_exist(app->scenes->group_info_dwindow->l_sc_members, json_object_get_string(juser_id), &row_index);
    // mx_log_err("test.txt", "row index, user id, last member index");
    // mx_log_err("test.txt", mx_itoa(row_index));
    // mx_log_err("test.txt", (char*)json_object_get_string(juser_id));
    // mx_log_err("test.txt", mx_itoa(app->last_member_widget_index));
    if (member_box != NULL) {        
        is_exist = true;
        GList *children = gtk_container_get_children(GTK_CONTAINER(member_box));

        img_member = children->data;
        children = g_list_next(children);

        l_member_name = children->data;
        children = g_list_next(children);

        b_delete = children->data;
        
        if (row_index < app->last_member_widget_index) {
            // mx_log_err("test.txt", "last member index is higher than row index");
            for (int i = app->last_member_widget_index; i < (int)g_list_length(gtk_container_get_children(GTK_CONTAINER(app->scenes->group_info_dwindow->l_sc_members))); i++) {
                // gtk_widget_destroy(mx_get_widget_from_list(app->scenes->group_info_dwindow->l_sc_members, i));
                gtk_widget_destroy(GTK_WIDGET(gtk_list_box_get_row_at_index(GTK_LIST_BOX(app->scenes->group_info_dwindow->l_sc_members), i)));
                // mx_log_info("test.txt", "delete row on index (first loop)");
                // mx_log_info("test.txt", mx_itoa(i));
            }
            app->last_member_widget_index = 0;
        }
        for (int i = app->last_member_widget_index; i < row_index; i++) {
            gtk_widget_destroy(GTK_WIDGET(gtk_list_box_get_row_at_index(GTK_LIST_BOX(app->scenes->group_info_dwindow->l_sc_members), i)));
            // mx_log_info("test.txt", "delete row on index (second loop)");
            // mx_log_info("test.txt", mx_itoa(i));
        }
    } else {  
        GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
        GError *error = NULL;
        if (gtk_builder_add_from_file(builder, RESOURCE_GROUP_INFO_PATH, &error) == 0) {
            //mx_log_err(SYSLOG, "gtk: Error loading file");
            return;
        }
      
        is_exist = false;
        member_box = mx_get_widget(builder, "member_box");
        img_member = mx_get_widget(builder, "user_ingroup_image");
        l_member_name = mx_get_widget(builder, "user_ingroup_login");
        b_delete = mx_get_widget(builder, "delete_user_button");
    }
    app->last_member_widget_index++;

    mx_set_style(l_member_name);
    mx_set_style(b_delete);

    mx_add_css_class(l_member_name, "usual-label");
    mx_add_css_class(b_delete, "button1");
    
    
    
    gtk_label_set_text(GTK_LABEL(l_member_name), formatted_login);
    gtk_widget_set_name(b_delete, json_object_get_string(juser_id));
    gtk_widget_set_name(member_box, json_object_get_string(juser_id));

    gtk_widget_set_name(img_member, file_name);
    mx_set_image_widget_size(GTK_IMAGE(img_member), img_member, file_name);

    if (!app->is_admin && json_object_get_int(juser_id) != app->user_id)
        gtk_widget_hide(b_delete);
    if (!is_exist) {
        int* member_id = malloc(sizeof(int));

        *member_id = json_object_get_int(juser_id);
        t_callback_data* cbdata = mx_create_callback_data(app, member_id); // TODO: Free this after group info dwindow closure

        g_signal_connect(b_delete, "clicked", G_CALLBACK(mx_callback_remove_group_member), cbdata);

        gtk_list_box_insert(GTK_LIST_BOX(app->scenes->group_info_dwindow->l_sc_members), member_box, -1);
    }

    //g_object_unref(builder);
}
