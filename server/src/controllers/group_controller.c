#include "server.h"

int get_group(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;
    json_object *json =  json_object_new_array();

    struct json_object *jobj = json_tokener_parse(req);
    int group_id = json_object_get_int(json_object_object_get(jobj, "group_id"));
    

    mx_openDB(DATABASE_NAME, &db);
    char temp[256];
    sprintf(temp, "group_id = \'%d\'",
        group_id
    );
    
    mx_select_data(db, "GROUPS", "*", temp, json);
    if(res != NULL){
        const char *json_str = json_object_to_json_string(json);
        *res =  mx_strdup((char*)json_str);
    }
            
    sqlite3_close(db);

    return group_id;
}
int create_group(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jgroup_name = json_object_object_get(jobj, "group_name"); 
    struct json_object *juser_id= json_object_object_get(jobj, "user_id"); 
    
    t_group group;
    t_user user;
    mx_memset(&group.file_name, 0, sizeof(group.file_name));
    group.size = 0;
    mx_memset(&user.file_name, 0, sizeof(user.file_name));
    user.size = 0;
    strcpy(group.group_name, json_object_get_string(jgroup_name));
    user.user_id = json_object_get_int(juser_id);
    mx_openDB(DATABASE_NAME, &db);
    group.privacy = 0;
    group.group_id = mx_insert_group(db, &group);

    mx_insert_group_member(db, &group, &user);
    const char *json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

int delete_group(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;
    
    struct json_object *jobj = json_tokener_parse(req);
    int group_id = get_group(req, NULL);

    mx_openDB(DATABASE_NAME, &db);
    char temp[256];
    sprintf(temp, "group_id = \'%d\'; " ,
        group_id
    );
    mx_delete_data(db, "GROUPS", temp);
    const char *json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

int get_group_members(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;
    json_object *json_arr =  json_object_new_array();

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    int group_id = json_object_get_int(jgroup_id);
    mx_openDB(DATABASE_NAME, &db);

    char temp[256];
    sprintf(temp, "group_id = \'%d\';",
        group_id
    );
    mx_select_data(db, "GROUP_MEMBERS", "*", temp, json_arr);

    json_object *json_user_arr =  json_object_new_array();
    int arr_len = json_object_array_length(json_arr);
    for(int i = 0; i < arr_len; i++) {
        char* json_user_str = NULL;
        json_object* jarray_obj = json_object_array_get_idx(json_arr, i);
        const char* arr_obj_str = json_object_to_json_string(jarray_obj);
        get_users_by_id(arr_obj_str, &json_user_str);
        struct json_object *juser = json_tokener_parse(json_user_str);
        json_object_array_add(json_user_arr, juser);
        mx_strdel(&json_user_str);
    }

    const char *group_members_json_str = json_object_to_json_string(json_user_arr);
    *res =  mx_strdup((char*)group_members_json_str);
    sqlite3_close(db);
    
    return 0;
}


int insert_group_members(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    struct json_object *juser_id = json_object_object_get(jobj, "user_id"); 

    t_user user;
    t_group group;
    mx_memset(&group.file_name, 0, sizeof(group.file_name));
    group.size = 0;
    mx_memset(&user.file_name, 0, sizeof(user.file_name));
    user.size = 0;
    group.group_id = json_object_get_int(jgroup_id);
    user.user_id = json_object_get_int(juser_id);

    mx_openDB(DATABASE_NAME, &db);
    mx_insert_group_member(db, &group, &user);


    const char *group_members_json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)group_members_json_str);
    sqlite3_close(db);
    
    return 0;
}

int get_messages(const char* req, char** res) {
    if(req == NULL)
        return -1;
    
    json_object *json =  json_object_new_array();
    sqlite3* db;
    char temp[256];

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    int group_id = json_object_get_int(jgroup_id);
    mx_openDB(DATABASE_NAME, &db);
    if(mx_strstr(req, "message_id")) {
        struct json_object *jmessage_id = json_object_object_get(jobj, "message_id"); 
        int message_id = json_object_get_int(jmessage_id);
        mx_select_data(db, "MESSAGES", "*", temp, json);
        sprintf(temp, "group_id = \'%d\'AND message_id > \'%d\'" \
        "; " , group_id, message_id);
        mx_select_data(db, "MESSAGES", "*", temp, json);
    } 
    else {
        sprintf(temp, "group_id = \'%d\'; " , group_id);

        mx_select_data(db, "MESSAGES", "*", temp, json);
    }
    
    

   
    
    const char *json_str = json_object_to_json_string(json);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

int create_message(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jgroup_id = json_object_object_get(jobj, "group_id"); 
    struct json_object *juser_id = json_object_object_get(jobj, "user_id"); 
    struct json_object *jmessage= json_object_object_get(jobj, "message_text"); 
    struct json_object *jdtime = json_object_object_get(jobj, "sent_datatime");


    t_message message;
    message.group_id = json_object_get_int(jgroup_id);
    message.user_id = json_object_get_int(juser_id);
    char temp[256];
    json_object *json =  json_object_new_array();
    sprintf(temp, "user_id = \'%d\'", message.user_id );
    mx_openDB(DATABASE_NAME, &db);
    
    mx_select_data(db, "USERS", "nick_name", temp, json);
    json_object *json_nick = json_object_array_get_idx(json, 0);
    mx_strcpy(message.user_nick_name, json_object_get_string(json_object_object_get(json_nick, "nick_name")));

    sqlite3_close(db);
    
    mx_memset(&message.file_name, 0, sizeof(message.file_name));
    message.size = 0;
    mx_strcpy(message.message_text, json_object_get_string(jmessage));
    mx_strcpy(message.sent_datatime, json_object_get_string(jdtime));
    if(mx_strstr(req, "file_name") != NULL) {
        struct json_object *jfpath = json_object_object_get(jobj, "file_name");
        struct json_object *jfsize = json_object_object_get(jobj, "file_size");
        mx_strcpy(message.file_name, json_object_get_string(jfpath));
        message.size = json_object_get_int64(jfsize);
    }


    mx_openDB(DATABASE_NAME, &db);
    mx_insert_message(db, &message);
    
    const char *group_members_json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)group_members_json_str);
    sqlite3_close(db);
    
    return 0;
}
