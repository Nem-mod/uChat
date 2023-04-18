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
// #include "tables.h"

#define UNUSED __attribute__((unused))

#define IP "127.0.0.1"
#define SERVER 1
#define CLIENT 0
#define CERTPATH "client/cert+key/client.crt"
#define KEYPATH "client/cert+key/client.key"

#define RESOURCE_GUI_PATH       "client/Resources/gui/"
#define RESOURCE_SIGNIN_PATH    (RESOURCE_GUI_PATH "builder.ui")
#define RESOURCE_SIGNUP_PATH    (RESOURCE_GUI_PATH "builder.ui")
#define RESOURCE_CHAT_PATH      (RESOURCE_GUI_PATH "chats_window.glade")
#define RESOURCE_ADD_CONT_PATH      (RESOURCE_GUI_PATH "addcontact.glade")

typedef struct s_callback_data t_callback_data;

/* Enum for scene representation */
typedef enum s_SCENE {
    SIGNUP,
    SIGNIN,
    CHAT,
    ADD_CONTACT
}            t_SCENE;

typedef struct s_file {

    char* path;
    unsigned int size;

}              t_file;

typedef struct s_contact {
    
    char* name;
    // char* first_name;
    // char* last_name;
    t_file* icon;

}              t_contact;

typedef struct s_user {
    
    t_contact* user_info;
    unsigned int id;
    char* login;
    char* password;

}              t_user;

typedef struct s_message {
    
    char* text;
    t_file* file;
    t_contact* owner;

}              t_message;

typedef struct s_chat {

    char* name;
    t_file* icon;
    t_contact** members;
    t_message** messages;

}              t_chat;

/* Struct for openSSL connection */
typedef struct s_serv_connection {
    int port;                       // 
    int socket;                     // 
    SSL* ssl;                       // 
    SSL_CTX* ctx;                   // SSL Context
    int hs_result;                  // Handshake result 
    pthread_t listener_thread;      // Mutex for listening server
    char lbuffer[MAXBUFFER];        // Buffer for retrive message
    //pthread_t writer_mutex;       // Mutex for writing to server
}               t_serv_connection;


/* Struct which contains GtkWidgets for SignUp Scene*/
typedef struct s_signup_scene {
    GtkWidget *w_signup;        // Window signUp
    GtkWidget *e_f_login;       // Entry field {login}
    GtkWidget *e_f_password;    // Entry field {password}
    GtkWidget *e_f_password2;   // Entry field {repeat password}
    GtkWidget *e_f_firstName;   // Entry field {firstName}
    GtkWidget *e_f_lastName;    // Entry field {lastName}
    GtkWidget *b_signup;        // Button signUp
    GtkWidget *bl_signin;       // Button-link on signIn window
    t_callback_data* cbdata;    // Callback data

}              t_signup_scene;

/* Struct which contains GtkWidgets for SignIn Scene*/
typedef struct s_signin_scene {
    GtkWidget *w_signin;        // Window signIn
    GtkWidget *gr_signin;
    GtkWidget *e_f_login;       // Enter field {login}    
    GtkWidget *e_f_password;    // Enter field {password}
    GtkWidget *b_signin;        // Buttin signIn
    GtkWidget *bl_signup;       // Button-link on signUp window
    t_callback_data* cbdata;    // Callback data
}              t_signin_scene;

/* Struct which contains GtkWidgets for SignIn Scene*/
typedef struct s_add_contact {
    GtkWidget *w_add_contact; 
    GtkWidget *e_f_login;       // Enter field {login}    
    GtkWidget *b_add_contact;        // Buttin signIn
    GtkWidget *b_close;       // Button-link on signUp window
    t_callback_data* cbdata;    // Callback data
}              t_add_contact;


/* Struct wich contains GtkWidgets for chat Scene*/
typedef struct s_chat_scene {
    GtkWidget *w_chat;     
    GtkWidget *m_box;        
    GtkWidget *e_f_chats;
    GtkWidget *w_sc_chats;  // Window of scrollbar
    GtkWidget *v_sc_chats;  // Viewport of scrollbar
    GtkWidget *l_sc_chats;  // List of objects of scrollbar
    GtkWidget *b_add_contact;
    
    
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
    t_add_contact* add_contact_dwindow;

}              t_uchat_scenes;


/* Struct of client application where main data is stored*/
typedef struct s_uchat_application {
    t_serv_connection* serv_connection;     // Server connection structure
    //GtkApplication* gtk_app;              // Link to Gtk application 
    //GtkCssProvider *css_provider;         // Link to CSS provider
    t_uchat_scenes* scenes;                 // Link to gui scenes
    t_SCENE active_scene;                   // Flag which one scene is active
    //t_user* user;                           // Information about the user
    int user_id;

}              t_uchat_application;

/* JSON response structure */
typedef struct s_response {   
    const char* type;       // Type of response (POST, GET, PATCH, DELETE)
    const char* url;        // Url of response (/auth/me, /auth/register and et)
    const char* property;   // Additional Data of response
    int status;             // Status of response (200 - OK, 400 - Bad request and et)
    
}              t_response;

/* Structure for pass data and t_uchat_application at once in callbacks*/
typedef struct s_callback_data {
    t_uchat_application* app;   // Application structure where main data is stored
    void* data;                 // Additional data to transfer 

}              t_callback_data;

// typedef struct s_chat {
//     t_group* group_info;
//     t_group_member** group_members;
//     t_message** messages;
// }               t_chat;


//  =============================================Callbacks=============================================
void mx_callback_change_scene(UNUSED GtkButton *button, gpointer data);
void mx_callback_registration(UNUSED GtkButton *button, gpointer data);
void mx_callback_auth(UNUSED GtkButton *button, gpointer data);
void mx_hide_window(UNUSED GtkButton *button, gpointer data);
void mx_callback_add_contact(UNUSED GtkButton *button, gpointer data);
//  =============================================Cleaners=============================================
void mx_clear_app(UNUSED GtkWindow *window, void* data);
void mx_clear_entry(GtkEntry *entry);
void mx_clear_server_connection(t_serv_connection* s_con);

//  =============================================Connection=============================================
void* mx_listen_server(void* data);
void mx_write_to_server(SSL* ssl, char* buffer);

//  =============================================Creators=============================================
t_uchat_application* mx_create_app(char* argv[]);
t_callback_data* mx_create_callback_data(t_uchat_application* app, void* data);
void mx_create_scenes(t_uchat_application* app);
GtkWidget *mx_get_widget(GtkBuilder *builder, char *id);
void mx_init_callbacks_signin(t_uchat_application* app);
void mx_init_callbacks_signup(t_uchat_application* app);
void mx_init_callbacks_chat(t_uchat_application* app);

void mx_init_add_cont(t_uchat_application* app);
void mx_init_scene_signin(t_uchat_application* app);
void mx_init_scene_signup(t_uchat_application* app);
void mx_init_scene_chat(t_uchat_application* app);
void mx_init_server_connection(t_uchat_application* app, int port);
void mx_init_scene_add_contact(t_uchat_application* app);

t_user* mx_create_user(char* login, char* pw, int id, char* name, char* icon_path, int size);
t_contact* mx_create_contact(char* name, char* icon_path, int size);
t_file* mx_create_file(char* path, int size);

//  =============================================Handlers=============================================
gboolean mx_handler_change_scene(gpointer data);
int mx_main_handler(char* json, t_uchat_application* app);

//  =============================================Json=============================================
/* Creates request for the server */
char* mx_create_request(char* type, char* url, json_object* prop);  

/* Disassemble given JSON and puts information in t_response */
t_response *mx_get_response(char* json);
// int mx_get_user_data(char* property);
char* mx_json_get_str(const char* property, char* id);
int mx_json_get_int(const char* property, char* id);
t_user* mx_json_create_user(const char* property);

//  =============================================Validators=============================================

//  =============================================Other=============================================
/* Hide current scene and show another */
void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene); 
