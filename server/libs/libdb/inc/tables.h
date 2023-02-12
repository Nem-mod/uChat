#include "sqlite3.h"
typedef struct s_user {
    int user_id;
    char* login;
    char* password;
    char* nick_name;
    char* first_name;
    char* last_name;
    sqlite3_blob* profile_photo;
}              t_user;


typedef struct s_contact {
    int contact_id;
    int user_id;
}              t_contact;

typedef struct s_group {
    int group_id;
    char* group_name;
}              t_group;

typedef struct s_group_member {
    int group_member_id;
    int group_id;
    int user_id;
}              t_group_member;

typedef struct s_message {
    int message_id;
    int group_id;
    int user_id;
    char* message_text;
    char* sent_datatime;
    sqlite3_blob* message_file;
    int file_size;
}              t_message;



