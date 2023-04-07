#pragma once

#include <stdio.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include <ctype.h>
#include <strings.h>
#include <sys/stat.h>
#include <json.h>
// #include <regex.h>

#include "client_utils.h"
#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"
#include "tables.h"

#define IP "127.0.0.1"
#define CERTPATH "client/cert+key/client.crt"
#define KEYPATH "client/cert+key/client.key"

#define RESOURCE_GUI_PATH "client/Resources/gui/"

typedef struct s_callback_data t_callback_data;

typedef enum s_SCENE {
    SIGNUP,
    SIGNIN
}            t_SCENE;

/* Struct for openSSL connection */
typedef struct s_serv_connection {
    int port;                       //
    int socket;                     // 
    SSL* ssl;                       // 
    SSL_CTX* ctx;                   // Context
    int hs_result;                  // 
    pthread_t listener_thread; // mutex for listening server
    char lbuffer[MAXBUFFER];        // buffer for retrive message
    //pthread_t writer_mutex;   // mutex for writing to server
}               t_serv_connection;


/* Struct wich contains GtkWidgets for SignUp Scene*/
typedef struct s_signup_scene {
    GtkWidget *w_signup;      // window signUp
    GtkWidget *e_f_login;     // entry field {login}
    GtkWidget *e_f_password;  // entry field {password}
    GtkWidget *e_f_password2; // entry field {repeat password}
    GtkWidget *e_f_firstName; // entry field {firstName}
    GtkWidget *e_f_lastName;  // entry field {lastName}
    GtkWidget *b_signup;      // button signUp
    GtkWidget *bl_signin;     // button-link on signIn window
    t_callback_data* cbdata;

}              t_signup_scene;

typedef struct s_signin_scene {
    GtkWidget *w_signin;        // window signIn
    GtkWidget *e_f_login;       // enter field {login}    
    GtkWidget *e_f_password;    // enter field {password}
    GtkWidget *b_signin;        // buttin signIn
    GtkWidget *bl_signup;       // button-link on signUp window
    t_callback_data* cbdata;
}              t_signin_scene;

/* Struct wich contain specific app scenes */
typedef struct s_uchat_scenes {
    t_signup_scene* signup_scene; // Sign up scene
    t_signin_scene* signin_scene; // Sign in scene

}              t_uchat_scenes;


/* Struct of client application where main data is stored*/
typedef struct s_uchat_application {
    t_serv_connection* serv_connection; // server connection
    //GtkApplication* gtk_app;            // link to Gtk application 
    //GtkCssProvider *css_provider;       // link to CSS provider
    t_uchat_scenes* scenes;              // link to gui scenes
    t_SCENE active_scene;                   // flag which one scene is active

}              t_uchat_application;

typedef struct s_response {   
    const char* type;
    const char* url;
    const char* property;
    int status;
    
}              t_response;

typedef struct s_callback_data {
    t_uchat_application* app;
    void* data;

}              t_callback_data;

// typedef struct s_

// typedef struct s_chat {
//     t_group* group_info;
//     t_group_member** group_members;
//     t_message** messages;
// }               t_chat;


/* Connect to server function*/
void mx_init_server_connection(t_uchat_application* app, int port);
void* mx_listen_server(void* data);
void mx_write_to_server(SSL* ssl, char* buffer);

int main_handler(char* json);
t_uchat_application* mx_create_app(char* argv[]);
GtkWidget *mx_get_widget(GtkBuilder *builder, char *id);
void mx_create_scenes(t_uchat_application* app);
void mx_init_signup(GtkBuilder *builder, t_uchat_application* app);

/* Create a json string with type, url and property */
char* mx_create_str_jreq(char* type, char* url, json_object* prop);


/* GUI callbacks */
void mx_registratinon_callback(GtkButton *button, gpointer data);


/* Cleaning */
void mx_clear_server_connection(t_serv_connection* s_con);

void mx_clear_app(GtkWindow *window, void* data);

void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene);

void mx_button_change_scenes(GtkButton *button, gpointer data);

t_callback_data* mx_create_callback_data();
