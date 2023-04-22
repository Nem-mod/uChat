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

