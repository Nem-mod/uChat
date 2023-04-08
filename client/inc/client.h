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

/* Enum for scene representation */
typedef enum s_SCENE {
    SIGNUP,     // Signup
    SIGNIN      // Signin
}            t_SCENE;

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
    GtkWidget *e_f_login;       // Enter field {login}    
    GtkWidget *e_f_password;    // Enter field {password}
    GtkWidget *b_signin;        // Buttin signIn
    GtkWidget *bl_signup;       // Button-link on signUp window
    t_callback_data* cbdata;    // Callback data
}              t_signin_scene;

/* Struct wich contain specific app scenes */
typedef struct s_uchat_scenes {
    t_signup_scene* signup_scene; // Signup scene
    t_signin_scene* signin_scene; // Signin scene

}              t_uchat_scenes;


/* Struct of client application where main data is stored*/
typedef struct s_uchat_application {
    t_serv_connection* serv_connection;     // Server connection structure
    //GtkApplication* gtk_app;              // Link to Gtk application 
    //GtkCssProvider *css_provider;         // Link to CSS provider
    t_uchat_scenes* scenes;                 // Link to gui scenes
    t_SCENE active_scene;                   // Flag which one scene is active

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

// typedef struct s_

// typedef struct s_chat {
//     t_group* group_info;
//     t_group_member** group_members;
//     t_message** messages;
// }               t_chat;


//  ===Callbacks===
/* Callback wrapper of mx_change_scene() (Must pass t_callback_data in data)*/
void mx_callback_change_scene(UNUSED GtkButton *button, gpointer data);
/* Get information from registration fields, create JSON request and write it to the server*/ 
void mx_callback_registration(UNUSED GtkButton *button, gpointer data);

//  ===Cleaners===
/* Free memory in t_uchat_application structure */
void mx_clear_app(UNUSED GtkWindow *window, void* data);
/* Free memory in t_server_connection structure */
void mx_clear_server_connection(t_serv_connection* s_con);  

//  ===Connection===
/* Wait server to response */
void* mx_listen_server(void* data);                 
/* Pass buffer to the server */
void mx_write_to_server(SSL* ssl, char* buffer);    

//  ===Creators===
/* Initialize t_uchat_application structure */
t_uchat_application* mx_create_app(char* argv[]);                               
/* Create t_callback_data structure */
t_callback_data* mx_create_callback_data(t_uchat_application* app, void* data); 
/* Initialize all scenes and put them in app */
void mx_create_scenes(t_uchat_application* app);                                
/* Gets GtkWidget by ID from builder */
GtkWidget *mx_get_widget(GtkBuilder *builder, char *id);                        
/* Initialize and put signin scene from builder into app */
void mx_init_scene_signin(GtkBuilder *builder, t_uchat_application* app);       
/* Initialize and put signup scene from builder into app */
void mx_init_scene_signup(GtkBuilder *builder, t_uchat_application* app);       
/* Initialize and put server connection into app */
void mx_init_server_connection(t_uchat_application* app, int port);             

//  ===Handlers===
/* Handler wrapper of mx_change_scene() (Must pass t_callback_data in data) */
gboolean mx_handler_change_scene(gpointer data);            
/* Handle server responses and calls relevate handler */
int mx_main_handler(char* json, t_uchat_application* app);  

//  ===Json===
/* Creates request for the server */
char* mx_create_request(char* type, char* url, json_object* prop);  
/* Disassemble given JSON and puts information in t_response */
t_response *mx_get_response(char* json);    

//  ===Validators===

//  ===Other===
/* Hide current scene and show another */
void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene); 
