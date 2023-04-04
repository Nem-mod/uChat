#pragma once

#include <stdio.h>
#include <unistd.h>

#include <gtk/gtk.h>

#include "client_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"

#define IP "127.0.0.1"
#define CERTPATH "client/cert+key/client.crt"
#define KEYPATH "client/cert+key/client.key"

#define RESOURCE_GUI_PATH "client/Resources/gui/"


/* Struct for openSSL conection */
typedef struct s_serv_connection {
    int port;                       //
    int socket;                     // 
    SSL* ssl;                       // 
    SSL_CTX* ctx;                   // Context
    int hs_result;                  //
    pthread_mutex_t listener_mutex; // mutex for listening server
    char lbuffer[MAXBUFFER];        // buffer for retrive message
    pthread_mutex_t writer_mutex;   // mutex for writing to server
    char wbuffer[MAXBUFFER];        // buffer for writing message
}               t_serv_connection;


/* Struct wich contains GtkWidgets for SignUp Scene*/
typedef struct s_signupWin {
    GtkWidget *w_signup;      // window signup
    GtkWidget *e_f_login;     // entry field {login}
    GtkWidget *e_f_password;  // entry field {password}
    GtkWidget *e_f_password2; // entry field {repeat password}
    GtkWidget *e_f_firstName; // entry field {firstName}
    GtkWidget *e_f_lastName;  // entry field {lastName}
    GtkWidget *b_signup;      // button signUp
    GtkWidget *bl_signin;     // button-link on signIn window

}              t_signupWin;


/* Struct wich contain specific app scenes */
typedef struct s_uchatScenes {
    t_signupWin* signUp_scene; // signUp scene

}              t_uchatScenes;


/* Struct of client application where main data is stored*/
typedef struct s_UchatApplication {
    t_serv_connection* serv_conection; // server conection
    GtkApplication* gtk_app;            // link to Gtk application 
    GtkCssProvider *css_provider;       // link to CSS provider
    t_uchatScenes* scenes;              // link to gui scenes
    int active_scene;                   // flag which one scene is active

}              t_UchatApplication;



/* Connect to server function*/
t_serv_connection *mx_init_server_conection(int port);
