#pragma once
#include "sqlite3.h"
#define MAX_LOGIN_LEN 32
#define MAX_NAME_LEN 64
#define MAX_PASSWORD_LEN 18
#define MAX_SENT_DATATIME_LEN 19
#define MAX_MESSAGE_TEXT_LEN 4096

typedef struct s_user {
    int user_id;
    char login[MAX_LOGIN_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    char nick_name[MAX_NAME_LEN + 1];
    char first_name[MAX_NAME_LEN + 1];
    char last_name[MAX_NAME_LEN + 1];
    char file_name[MAX_NAME_LEN + 1];
    unsigned int size;
}              t_user;

typedef struct s_tp {
    char login[10];
}              t_tp;


typedef struct s_contact {
    int contact_id;
    int user_id;
}              t_contact;

typedef struct s_group {
    int group_id;
    char group_name[MAX_NAME_LEN + 1];
    char file_name[MAX_NAME_LEN + 1];
    int privacy;
    unsigned int size;
}              t_group;

typedef struct s_group_member {
    int group_member_id;
    int group_id;
    unsigned int user_id;
}              t_group_member;

typedef struct s_message {
    int message_id;
    int group_id;
    int user_id;
    char message_text[MAX_MESSAGE_TEXT_LEN + 1];
    char sent_datatime[MAX_SENT_DATATIME_LEN + 1];
    char file_name[MAX_NAME_LEN + 1];
    char user_nick_name[MAX_NAME_LEN + 1];
    unsigned int size;
}              t_message;



