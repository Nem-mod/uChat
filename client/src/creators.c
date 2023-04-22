#include "client.h"

t_uchat_application* mx_create_app(char* argv[]) {
    t_uchat_application* app = malloc(sizeof(t_uchat_application));

    app->user_id = 0;
    app->current_group_id = 0;
    app->last_message_id = 0;
    app->choosed_file_pname = NULL;
    // app->skip_json_log = false;
    
    mx_create_scenes(app);
    mx_init_server_connection(app, mx_atoi(argv[1]));

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
    file->size = size; // TODO: create func to get file size

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
    GtkBuilder *builder = gtk_builder_new();    // TODO: Maybe needs free
    GError *error = NULL;

    if (gtk_builder_add_from_file(builder, RESOURCE_CHAT_PATH, &error) == 0) {
        // g_printerr("Error loading file: %s\n", error->message);
        // g_clear_error(&error);
        mx_log_err(SYSLOG, "gtk: Error loading file");
        return;
    }

    GtkWidget *chat_box = mx_get_widget(builder, "chat_box");
    GtkWidget *chat_button = mx_get_widget(builder, "chat_button");
    GtkWidget *chat_img = mx_get_widget(builder, "chat_img");
    GtkWidget *chat_name = mx_get_widget(builder, "chat_name");

    struct json_object* jobj = json_tokener_parse(res->property);
    if(res->property == NULL) 
        return;
    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    struct json_object *jgroup_privacy = json_object_object_get(jobj, "group_privacy"); 
    if(mx_check_widget_exist(app->scenes->chat_scene->l_sc_chats, json_object_get_string(jgroup_id)))
        return;
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
    
    gtk_label_set_text(GTK_LABEL(chat_name), (char*)json_object_get_string(jname));
    gtk_widget_set_name(chat_button,  mx_itoa(json_object_get_int(jgroup_id)));
    gtk_widget_set_name(chat_box,  mx_itoa(json_object_get_int(jgroup_privacy)));
    gtk_widget_set_name(chat_name, "chat_name");

    gtk_widget_set_name(chat_img, file_name);
    mx_set_image_widget_size(GTK_IMAGE(chat_img), chat_img, file_name);

    gtk_widget_set_size_request(chat_box, 10, 10);
    gtk_list_box_insert(GTK_LIST_BOX(app->scenes->chat_scene->l_sc_chats), chat_button, -1);
    g_signal_connect(chat_button, "clicked", G_CALLBACK (mx_callback_chatbox), app);
    g_object_unref(builder);
}

// void mx_create_new_member_widget(t_uchat_application* app, t_response* res) {

// }
