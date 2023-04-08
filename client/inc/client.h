#pragma once

#include <stdio.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include <ctype.h>
#include <strings.h>
#include <sys/stat.h>
#include <json.h>
// #include <regex.h>

#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"
#include "tables.h"

#define UNUSED __attribute__((unused))

#define IP "127.0.0.1"
#define SERVER 1
#define CLIENT 0
#define CERTPATH "client/cert+key/client.crt"
#define KEYPATH "client/cert+key/client.key"

#define RESOURCE_GUI_PATH "client/Resources/gui/"

typedef struct s_callback_data t_callback_data;

typedef enum s_SCENE {
    SIGNUP,
    SIGNIN,
    CHAT
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
    GThread* thread;
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

/* Struct wich contains GtkWidgets for chat Scene*/
typedef struct s_chat_scene {
    GtkWidget *w_chat;     
    GtkWidget *m_box;        
    GtkWidget *e_f_chats;
    GtkWidget *w_sc_chats;  // Window of scrollbar
    GtkWidget *v_sc_chats;  // Viewport of scrollbar
    GtkWidget *l_sc_chats;  // List of objects of scrollbar
    
    
    
    GtkWidget *w_sc_messages;  // Window of scrollbar
    GtkWidget *v_sc_messages;  // Viewport of scrollbar
    GtkWidget *l_sc_messages;  // List of objects of scrollbar
    GtkWidget *e_f_chat;
    GtkWidget *b_send_message;
    
    t_callback_data* cbdata;

}              t_chat_scene;

/* Struct wich contain specific app scenes */
typedef struct s_uchat_scenes {
    t_signup_scene* signup_scene; // Sign up scene
    t_signin_scene* signin_scene; // Sign in scene
    t_chat_scene* chat_scene;
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


//  ===Creators===
t_uchat_application* mx_create_app(char* argv[]);
t_callback_data* mx_create_callback_data(t_uchat_application* app, void* data);
void mx_create_scenes(t_uchat_application* app);

/* Get GtkWidget from GtkObj function */
GtkWidget *mx_get_widget(GtkBuilder *builder, char *id);

//  ===Connection===
void* mx_listen_server(void* data);
void mx_write_to_server(SSL* ssl, char* buffer);

// ===Init Scenes===
void mx_init_scene_signin(GtkBuilder *builder, t_uchat_application* app);
void mx_init_scene_signup(GtkBuilder *builder, t_uchat_application* app);
void mx_init_scene_chat(GtkBuilder *builder, t_uchat_application* app);
void mx_init_server_connection(t_uchat_application* app, int port);

//  ===Handlers===
gboolean mx_handler_change_scene(gpointer data);
int mx_main_handler(char* json, t_uchat_application* app);

//  ===Callbacks===
void mx_callback_change_scene(UNUSED GtkButton *button, gpointer data);
void mx_callback_registration(UNUSED GtkButton *button, gpointer data);
void mx_callback_auth(UNUSED GtkButton *button, gpointer data);


//  ===Validators===


//  ===Json===
char* mx_create_request(char* type, char* url, json_object* prop);
t_response *mx_get_response(char* json);

//  ===Cleaners===
void mx_clear_app(UNUSED GtkWindow *window, void* data);
void mx_clear_server_connection(t_serv_connection* s_con);


//  ===Other===
void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene);
