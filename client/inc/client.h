#pragma once

#include <stdio.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include <ctype.h>
#include <strings.h>
#include <sys/stat.h>
#include <json.h>
#include <regex.h>
#include <math.h>

#include "connect_utils.h"
#include "ssl_utils.h"
#include "log_utils.h"
#include "libmx.h"
// #include "tables.h"

#define UNUSED __attribute__((unused))

#define IP "127.0.0.1"
#define SERVER 1
#define CLIENT 0
#define PING_SERVER_LONG_INTERVAL_SECONDS 2
#define PING_SERVER_SHORT_INTERVAL_MILISECONDS 200
#define CERTPATH "client/cert+key/client.crt"
#define KEYPATH "client/cert+key/client.key"

#define RESOURCE_ICONS_PATH "client/Resources/icons/"
#define RESOURCE_BASE_ICON "client/Resources/icons/base.png"
#define RESOURCE_BASE_GROUP_ICON "client/Resources/icons/base-group.png"
#define RESOURCE_PATH       "./client/Resources/"
#define RESOURCE_DEFAULT_IMAGE "client/Resources/icons/default-image.png"
#define RESOURCE_GUI_PATH       "client/Resources/gui/"

#define RESOURCE_SIGNIN_PATH    (RESOURCE_GUI_PATH "builder.ui")
#define RESOURCE_SIGNUP_PATH    (RESOURCE_GUI_PATH "builder.ui")
#define RESOURCE_CHAT_PATH      (RESOURCE_GUI_PATH "chats_window.glade")
#define RESOURCE_ADD_CONT_PATH      (RESOURCE_GUI_PATH "addcontact.glade")
#define RESOURCE_CREATE_GROUP_PATH      (RESOURCE_GUI_PATH "addgroup.glade")
#define RESOURCE_PROFILE_WINDOW_PATH      (RESOURCE_GUI_PATH "profile_window.glade")
#define RESOURCE_GROUP_INFO_PATH    (RESOURCE_GUI_PATH "edit_group.glade")

typedef struct s_callback_data t_callback_data;

/* Enum for scene representation */
typedef enum s_SCENE {
    SIGNUP,
    SIGNIN,
    CHAT,
    ADD_CONTACT,
    CREATE_GROUP,
    PROFILE,
    GROUP_INFO
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
    GtkWidget *l_signup;        // Label signup field
    GtkWidget *l_welcome;       // Label welcome field

    GtkWidget *l_first_name_err;
    GtkWidget *l_second_name_err;
    GtkWidget *l_login_err;
    GtkWidget *l_password_err;
    GtkWidget *l_repeat_password_err;
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
    GtkWidget *l_err_msg;       // Error message label ("Wrong password or login")
    GtkWidget *l_signin;       // Label signin field
    GtkWidget *l_welcome;       // Label welcome field
    t_callback_data* cbdata;    // Callback data
}              t_signin_scene;

typedef struct s_add_contact {
    GtkWidget *w_add_contact; 
    GtkWidget *l_add_contact;
    GtkWidget *e_f_login;       
    GtkWidget *b_add_contact;        
    GtkWidget *b_close;       
    t_callback_data* cbdata;    
}              t_add_contact_scene;

typedef struct s_create_group {
    GtkWidget *w_create_group; 
    GtkWidget *l_create_group;
    GtkWidget *e_f_group_name;            
    GtkWidget *b_create_group;        
    GtkWidget *b_close;       
    t_callback_data* cbdata;    
}               t_create_group_scene;

typedef struct s_user_profile {
    GtkWidget *w_user_profile; 
    GtkWidget *l_profile;
    GtkWidget *l_login;
    GtkWidget *l_user_login;        
    GtkWidget *img_user;        
    GtkWidget *bc_file;            
    GtkWidget *b_logout;       
    GtkWidget *b_confirm;
    GtkWidget *b_cancel;
    t_callback_data* cbdata;    
}               t_user_profile_scene;

/* Struct wich contains GtkWidgets for chat Scene*/
typedef struct s_chat_scene {
    GtkWidget *w_chat;     
    GtkWidget *m_box;        
    GtkWidget *e_f_chats;
    GtkWidget *w_sc_chats;  // Window of scrollbar
    GtkWidget *v_sc_chats;  // Viewport of scrollbar
    GtkWidget *l_sc_chats;  // List of objects of scrollbar
    GtkWidget *b_add_contact;
    GtkWidget *b_add_group;
    
    GtkWidget *b_chat_settings;
    GtkWidget *w_sc_messages;  // Window of scrollbar
    GtkWidget *v_sc_messages;  // Viewport of scrollbar
    GtkWidget *l_sc_messages;  // List of objects of scrollbar
    GtkWidget *img_chat;
    GtkWidget *l_chatname;
    GtkWidget *e_f_chat;
    GtkWidget *e_f_file;
    GtkWidget *b_send_message;
    GtkWidget *bc_file;
    GtkWidget *b_chat_profile;
    GtkWidget *f_fixed;
    
    GtkWidget *img_user;
    GtkWidget *b_profile;

    GtkWidget *s_separator1;
    GtkWidget *s_separator2;
    GtkWidget *s_separator3;

    t_callback_data* cbdata;

}              t_chat_scene;

typedef struct s_group_info_scene {
    GtkWidget* w_group_info;
    GtkWidget* l_group_info;
    GtkWidget* e_f_new_group_member;
    GtkWidget* b_add_member;
    GtkWidget* b_close;
    
    GtkWidget* w_sc_members;
    GtkWidget* v_sc_members;
    GtkWidget* l_sc_members;

    GtkWidget* img_group;
    GtkWidget* e_f_new_group_name;
    GtkWidget* b_confirm;
    GtkWidget* bc_file;

    t_callback_data* cbdata;

}               t_group_info_scene;

/* Struct wich contain specific app scenes */
typedef struct s_uchat_scenes {
    t_signup_scene* signup_scene; // Sign up scene
    t_signin_scene* signin_scene; // Sign in scene
    t_chat_scene* chat_scene;
    t_add_contact_scene* add_contact_dwindow;
    t_create_group_scene* create_group_dwindow;
    t_user_profile_scene* user_profile_dwindow;
    t_group_info_scene* group_info_dwindow;
}              t_uchat_scenes;

// typedef struct s_choosed_files {
//     char* message_file;
//     char* profile_image;
//     char* group_image;
// }               t_choosed_files;

/* Struct of client application where main data is stored*/
typedef struct s_uchat_application {
    t_serv_connection* serv_connection;     // Server connection structure
    //GtkApplication* gtk_app;              // Link to Gtk application 
    //GtkCssProvider *css_provider;         // Link to CSS provider
    t_uchat_scenes* scenes;                 // Link to gui scenes
    t_SCENE active_scene;                   // Flag which one scene is active
   
    int user_id;
    int current_group_id;
    int last_message_id;
    int last_message_indx;
    bool is_admin;
    int last_member_widget_index;
    int last_group_widget_index;

    char* choosed_file_pname;

    // bool skip_json_log;
    // TODO: add current position of scene
}              t_uchat_application;

/* JSON response structure */
typedef struct s_response {   
    char* type;       // Type of response (POST, GET, PATCH, DELETE)
    char* url;        // Url of response (/auth/me, /auth/register and et)
    char* property;   // Additional Data of response
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
void mx_callback_hide_window(UNUSED GtkButton *button, gpointer data);
void mx_callback_add_contact(UNUSED GtkButton *button, gpointer data);
void mx_callback_chatbox(UNUSED GtkButton *button, gpointer data);
void mx_callback_send_message(UNUSED GtkButton *button, gpointer data);
void mx_callback_create_group(UNUSED GtkButton *button, gpointer data);
void mx_callback_choose_file(GtkFileChooserButton *button, gpointer data);
void mx_callback_test(UNUSED GtkButton *button, UNUSED gpointer data);
void mx_callback_log_out(UNUSED GtkButton *button, UNUSED gpointer data);
void mx_callback_hide_window_crt(UNUSED GtkButton *button, gpointer data);
void mx_callback_hide_window_group_info(UNUSED GtkButton *button, gpointer data);
void mx_callback_hide_profile(UNUSED GtkButton *button, gpointer data);
void mx_callback_patch_user(UNUSED GtkButton *button, gpointer data);
void mx_init_callbacks_group_info(t_uchat_application* app);
void mx_auth_callback(t_uchat_application* app, t_response* res);
void mx_callback_set_up_profile_image(UNUSED GtkButton *button, UNUSED gpointer data);
void mx_callback_search_by_chats(UNUSED GtkButton *button, gpointer data);
gboolean mx_callback_on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
void mx_callback_group_info(UNUSED GtkButton *button, gpointer data);
void mx_callback_add_group_member(UNUSED GtkButton *button, gpointer data);
void mx_callback_set_up_group_image(UNUSED GtkButton *button, UNUSED gpointer data);
void mx_callback_patch_group(UNUSED GtkButton *button, gpointer data);
void mx_callback_hide_chatbox(UNUSED GtkButton *button, gpointer data);
void mx_callback_show_chatbox(UNUSED GtkButton *button, gpointer data);
void mx_callback_remove_group_member(UNUSED GtkButton *button, gpointer data);
gboolean mx_clear_res(gpointer data);
//  =============================================Cleaners=============================================
void mx_clear_app(UNUSED GtkWindow *window, void* data);
void mx_clear_entry(GtkEntry *entry);
void mx_clear_server_connection(t_serv_connection* s_con);

//  =============================================Connection=============================================
void* mx_listen_server(void* data);
void mx_write_to_server(SSL* ssl, char* buffer);
unsigned long mx_handle_post_file(char* req, char** filename);

//  =============================================Creators=============================================
t_uchat_application* mx_create_app(char* argv[]);
t_callback_data* mx_create_callback_data(t_uchat_application* app, void* data);
void mx_create_scenes(t_uchat_application* app);
GtkWidget *mx_get_widget(GtkBuilder *builder, char *id);
void mx_init_callbacks_signin(t_uchat_application* app);
void mx_init_callbacks_signup(t_uchat_application* app);
void mx_init_callbacks_chat(t_uchat_application* app);
void mx_init_callbacks_user_profile(t_uchat_application* app);
void mx_init_scene_create_group(t_uchat_application* app);
void mx_init_callbacks_add_contact(t_uchat_application* app);
void mx_init_callbacks_create_group(t_uchat_application* app);
void mx_init_scene_signin(t_uchat_application* app);
void mx_init_scene_signup(t_uchat_application* app);
void mx_init_scene_chat(t_uchat_application* app);
void mx_init_server_connection(t_uchat_application* app, int port);
void mx_init_scene_add_contact(t_uchat_application* app);
void mx_init_scene_create_group(t_uchat_application* app);
void mx_init_scene_user_profile(t_uchat_application* app);
void mx_init_scene_group_info(t_uchat_application* app);

void mx_create_new_chat_widget(t_uchat_application* app, t_response* res); 
void mx_create_new_member_widget(t_uchat_application* app, t_response* res);
t_user* mx_create_user(char* login, char* pw, int id, char* name, char* icon_path, int size);
t_contact* mx_create_contact(char* name, char* icon_path, int size);
t_file* mx_create_file(char* path, int size);
void mx_set_style(GtkWidget *widget);
void mx_set_image_widget_size(GtkImage* image, GtkWidget* widget_to_shrink, const char* filename);
void mx_add_css_class(GtkWidget *widget, const char *classname);
void mx_set_image_limit_size(GtkImage* image, GtkWidget* widget_to_shrink, const char* filename);

//  =============================================Handlers=============================================
gboolean mx_handler_change_scene(gpointer data);
gboolean mx_handler_create_new_chat_widget(gpointer data);
gboolean mx_handler_create_new_member_widget(gpointer data);
gboolean mx_handler_display_messages(gpointer data);
void mx_handle_messages_res(t_uchat_application* app, t_response* res);
int mx_main_handler(char* json, t_uchat_application* app);
gboolean mx_handler_ping_server_get_chats(gpointer data);
gboolean mx_handler_ping_server_get_messages(gpointer data);
gboolean mx_handler_ping_server_get_group_members(gpointer data);
gboolean mx_handler_chat_scroll_down(gpointer data);
gboolean mx_handler_auth(gpointer data);
void mx_handler_hide_chatbox(gpointer data);
void mx_handler_show_chatbox(gpointer data);

//  =============================================Json=============================================
/* Creates request for the server */
char* mx_create_request(char* type, char* url, json_object* prop);  

/* Disassemble given JSON and puts information in t_response */
t_response *mx_get_response(char* json);
int mx_json_get_int(const char* property, const char* obj);
char* mx_json_get_string(const char* property, const char* obj);

//  =============================================Validators=============================================
GtkWidget* mx_check_widget_exist(GtkWidget *list_box, const char* desired_name, int* index);
int mx_validate_password_digits(const char *password);
int mx_validate_password_letters(const char *password);

//  =============================================Other=============================================
/* Hide current scene and show another */
void mx_change_scenes(t_uchat_application* app, t_SCENE new_scene); 
GtkWidget* mx_gtk_find_child(GtkWidget* parent, const gchar* name);
GtkWidget* mx_get_widget_from_list(GtkWidget* list, int index);

