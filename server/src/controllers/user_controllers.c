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
    struct json_object *juser_contact_id= json_object_object_get(jobj, "user_contact_id"); 

    mx_openDB(DATABASE_NAME, &db);
    mx_insert_contact(db, json_object_get_int(juser_id), json_object_get_int(juser_contact_id));
    const char *json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    
    return 0;
}

