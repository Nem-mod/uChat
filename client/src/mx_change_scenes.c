#include "client.h"

void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene) {
    gtk_widget_hide(app->scenes->signin_scene->w_signin);
    gtk_widget_hide(app->scenes->signup_scene->w_signup);
    
    mx_printstr("Scene changing\n");
    mx_printint(new_scene);
    mx_printchar('\n');
    switch(new_scene) {
        case SIGNUP:
            gtk_widget_show(app->scenes->signup_scene->w_signup);
            break;
        case SIGNIN:
            gtk_widget_show(app->scenes->signin_scene->w_signin);
            break;
        default:
            break;
    }
    gtk_main();
}
