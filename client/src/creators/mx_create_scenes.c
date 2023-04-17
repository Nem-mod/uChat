#include "client.h"

void mx_create_scenes(t_uchat_application* app) {
    app->scenes = malloc(sizeof(t_uchat_scenes));
    mx_init_scene_chat(app);
    mx_init_scene_signin(app);
    mx_init_scene_signup(app);

    mx_init_callbacks_chat(app);
    mx_init_callbacks_signin(app);
    mx_init_callbacks_signup(app);
}
