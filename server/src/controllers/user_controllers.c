#include "server.h"

int getAll_users(const char* req, char** res) {
    if(req == NULL)
        return -1;
    
    json_object *json =  json_object_new_array();
    sqlite3* db;
    mx_openDB(DATABASE_NAME, &db);
    mx_select_data(db, "USERS", "*", NULL, json);
    const char *json_str = json_object_to_json_string(json);
    *res = mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}


int get_users_by_name(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    json_object *json =  json_object_new_array();
    sqlite3* db;
    
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jlogin = json_object_object_get(jobj, "login"); 
    struct json_object *jnick = json_object_object_get(jobj, "nick_name"); 

    char temp[256];
    const char* login = json_object_get_string(jlogin);
    const char* nick_name = json_object_get_string(jnick);

    sprintf(temp, "login = \'%s\' " \
        "OR nick_name = \'%s\';",
        login, nick_name
    );

    mx_openDB(DATABASE_NAME, &db);
    mx_select_data(db, "USERS", "*", temp, json);
    const char *json_str = json_object_to_json_string(json);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

int get_users_by_id(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    json_object *json =  json_object_new_array();
    sqlite3* db;

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *juser_id = json_object_object_get(jobj, "user_id"); 

    char temp[256];
    int user_id = json_object_get_int(juser_id);

    sprintf(temp, "user_id = \'%d\';",
        user_id
    );

    mx_openDB(DATABASE_NAME, &db);
    mx_select_data(db, "USERS", "*", temp, json);
    const char *json_str = json_object_to_json_string(json);

    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

int add_contact(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;

    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *juser_id= json_object_object_get(jobj, "user_id"); 
    struct json_object *juser_login= json_object_object_get(jobj, "login"); 
    
    mx_openDB(DATABASE_NAME, &db);

    char temp[256];

    sprintf(temp, "login = \'%s\' ;",
        json_object_get_string(juser_login)
    );

    json_object *json =  json_object_new_array();
    mx_select_data(db, "USERS", "*", temp, json);

    json_object *jcont_id = json_object_object_get(json_object_array_get_idx(json, 0), "user_id");
    if (!jcont_id || json_object_is_type(jcont_id, json_type_null)) {
        return -1;
    }
    int user1_id = json_object_get_int(juser_id);
    int user2_id = json_object_get_int(jcont_id);
    
    if (user2_id == 0 || user1_id == user2_id) {
        return -1;
    }
    

    if(mx_insert_contact(db, user1_id, user2_id) != -1) {
       
        t_group group;
        mx_strcpy(group.group_name, json_object_get_string(juser_login));
        group.privacy = 1;

        group.group_id = mx_insert_group(db, &group);

        t_user user1, user2;
        user1.user_id = user1_id;
        user2.user_id = user2_id;
        mx_insert_group_member(db, &group, &user1);
        mx_insert_group_member(db, &group, &user2);

        json_object_object_add(jobj, "group_id", json_object_new_int(group.group_id));
        json_object_object_add(jobj, "group_privacy", json_object_new_int(group.privacy));
    }
    
    const char *json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

int get_user_groups(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;
    json_object *json =  json_object_new_array();
    json_object *json_finaly=  json_object_new_array();
    struct json_object *jobj = json_tokener_parse(req);
    int user_id = json_object_get_int(json_object_object_get(jobj, "user_id"));
    

    mx_openDB(DATABASE_NAME, &db);
    char temp[256];
    sprintf(temp, "user_id = \'%d\'",
        user_id
    );
    
    mx_select_data(db, "GROUP_MEMBERS", "*", temp, json);

    if (json_object_is_type(json, json_type_array)) {
        
        for(size_t i = 0; i < json_object_array_length(json); i++) {
            json_object* jind = json_object_array_get_idx(json, i);
            json_object *jg_id = json_object_object_get(jind, "group_id");
            int group_id = json_object_get_int(jg_id);
            
            mx_memset(&temp, 0, sizeof(temp));
            sprintf(temp, "group_id = \'%d\'",
                group_id
            );


            json_object *json_g =  json_object_new_array();
            
            mx_select_data(db, "GROUPS", "*", temp, json_g);

            json_object *jprivacy = json_object_object_get(json_object_array_get_idx(json_g, 0), "group_privacy");

            if(json_object_get_int(jprivacy) == 0) {
                
                json_object_array_add(json_finaly, json_object_array_get_idx(json_g, 0));
            } 
            else {
                json_object *json_u =  json_object_new_array();
                mx_memset(&temp, 0, sizeof(temp));
                sprintf(temp, "user_id IN (" \
                    "SELECT user_id " \
                    "FROM GROUP_MEMBERS " \
                    "WHERE group_id = \'%d\' AND user_id != \'%d\' " \
                    ");",
                    group_id,
                    user_id
                );
                mx_select_data(db, "USERS", "user_id, nick_name, first_name, last_name, file_name, file_size", temp, json_u);
                json_object *json_c = json_object_array_get_idx(json_u, 0);
                json_object_object_add(json_c, "group_id", json_object_new_int(group_id));
                json_object_object_add(json_c, "group_privacy", json_object_new_int(1));
                json_object_array_add(json_finaly, json_c);
            }
        }

        
    } 
    
    const char *json_str = json_object_to_json_string(json_finaly);
    *res =  mx_strdup((char*)json_str);
            
    sqlite3_close(db);

    return 0;
}


int patch_user(const char* req, char** res){
    if(req == NULL)
        return -1;
    
    sqlite3* db;
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *juser_id = json_object_object_get(jobj, "user_id"); 
    if(mx_strstr(req, "file_name") != NULL) {
        struct json_object *jfpath = json_object_object_get(jobj, "file_name");
        struct json_object *jfsize = json_object_object_get(jobj, "file_size");
        char* file_name =  (char*)json_object_get_string(jfpath);
        char temp[256];
        char where[256];
        int user_id = json_object_get_int(juser_id);

        unsigned int file_size = (unsigned int)json_object_get_int64(jfsize);
        sprintf(temp, "file_name = \'%s\', file_size = %d",
                file_name, file_size
        );
        sprintf(where, "user_id = \'%d\'",
                user_id
        );
        mx_openDB(DATABASE_NAME, &db);
        mx_update_data(db, "USERS", where, temp, NULL);
        sqlite3_close(db);

    }

    get_users_by_id(req, res);

    return 0;
}
