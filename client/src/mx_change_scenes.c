#include "client.h"

void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene) {
    gtk_widget_hide(app->scenes->signin_scene->w_signin);
    gtk_widget_hide(app->scenes->signup_scene->w_signup);
    
    //mx_log_info(SYSLOG, "Scene changing");
    
    switch(new_scene) {
        case SIGNUP:
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_login_err), "");
            gtk_entry_set_text(GTK_ENTRY(app->scenes->signin_scene->e_f_login), "");
            gtk_entry_set_text(GTK_ENTRY(app->scenes->signin_scene->e_f_password), "");
 
            gtk_widget_show(app->scenes->signup_scene->w_signup);
            app->active_scene = SIGNUP;
            break;
        case SIGNIN:
            gtk_label_set_text(GTK_LABEL(app->scenes->signin_scene->l_err_msg), "");
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_password_err), "");   
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_first_name_err), "");
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_second_name_err), "");
            gtk_label_set_text(GTK_LABEL(app->scenes->signup_scene->l_repeat_password_err), "");
            
            mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_login));
            mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_password));
            mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_password2));
            mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_firstName));
            mx_clear_entry(GTK_ENTRY(app->scenes->signup_scene->e_f_lastName));

            gtk_widget_show(app->scenes->signin_scene->w_signin);
            app->active_scene = SIGNIN;
            break;
        case CHAT:
            mx_strdel(&app->choosed_file_pname);
            gtk_widget_show(app->scenes->chat_scene->w_chat);
            app->active_scene = CHAT;
            break;
        case ADD_CONTACT:
            gtk_widget_show(app->scenes->add_contact_dwindow->w_add_contact);
            app->active_scene = ADD_CONTACT;
            break;
        case CREATE_GROUP:
            gtk_widget_show(app->scenes->create_group_dwindow->w_create_group);
            app->active_scene = CREATE_GROUP;
            break;
        case PROFILE:
            mx_strdel(&app->choosed_file_pname);
            gtk_widget_show(app->scenes->user_profile_dwindow->w_user_profile);
            app->active_scene = PROFILE;
        break;
        case GROUP_INFO:
            mx_strdel(&app->choosed_file_pname);
            gtk_widget_show(app->scenes->group_info_dwindow->w_group_info);
            app->active_scene = GROUP_INFO;
        break;
        default:
            break;
    }
}
