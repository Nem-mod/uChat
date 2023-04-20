#include "client.h"

void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene) {
    gtk_widget_hide(app->scenes->signin_scene->w_signin);
    gtk_widget_hide(app->scenes->signup_scene->w_signup);
    
    mx_log_info(SYSLOG, "Scene changing");
    
    switch(new_scene) {
        case SIGNUP:
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_login_err), "");
 
            gtk_widget_show(app->scenes->signup_scene->w_signup);
            break;
        case SIGNIN:
            gtk_label_set_text(GTK_LABEL(app->scenes->signin_scene->l_err_msg), "");
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "");   
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_first_name_err), "");
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_second_name_err), "");
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_repeat_password_err), "");

            gtk_widget_show(app->scenes->signin_scene->w_signin);
            break;
        case CHAT:
            gtk_widget_show(app->scenes->chat_scene->w_chat);
            break;
        case ADD_CONTACT:
            gtk_widget_show(app->scenes->add_contact_dwindow->w_add_contact);
            break;
        default:
            break;
    }
}
