#include "client.h"


void mx_init_signup(GtkBuilder* builder, t_signupScene* signUpScene) {
    builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file (builder, "client/Resources/gui/builder.ui", &error) == 0) {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return;
    }
    signUpScene->w_signup = mx_get_widget(builder, "signup_window");
    signUpScene->e_f_login = mx_get_widget(builder, "login_entry");
    signUpScene->e_f_password = mx_get_widget(builder, "password_entry");
    signUpScene->e_f_password2 = mx_get_widget(builder, "r_password_entry");
    signUpScene->e_f_firstName = mx_get_widget(builder, "fname_entry");
    signUpScene->e_f_lastName = mx_get_widget(builder, "lname_entry");
    signUpScene->b_signup = mx_get_widget(builder, "register_button");
    signUpScene->bl_signin = mx_get_widget(builder, "signin_link");
}

t_uchatScenes* mx_create_scenes() {
    t_uchatScenes* scenes = malloc(sizeof(t_uchatScenes));
    GtkBuilder* builder = NULL;
    scenes->signUp_scene = malloc(sizeof(t_signupScene));
    mx_init_signup(builder, scenes->signUp_scene);
    return scenes;
}
