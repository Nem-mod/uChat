#include "server.h"

int login(const char* req, char** res) {
    if(req == NULL)
        return -1;
    json_object *json =  json_object_new_array();
    sqlite3* db;
    
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jlogin = json_object_object_get(jobj, "login"); 
    struct json_object *jpass = json_object_object_get(jobj, "password");
    const char* login = json_object_get_string(jlogin);
    const char* password = json_object_get_string(jpass);

    char temp[256];
    sprintf(temp, "login = \'%s\' " \
        "AND password = \'%s\';",
        login, password
    );

    mx_openDB(DATABASE_NAME, &db);
    int id = mx_select_data(db, "USERS", "*", temp, json);
    const char *json_str = json_object_to_json_string(json);
    mx_printstr((char*)json_str);
    if(id < 0 || mx_strcmp(json_str, "[ ]") == 0) {
        *res =  mx_create_err_res("Auth error;");
        return -1;
    }
   
    *res =  mx_strdup((char*)json_str);
    
    sqlite3_close(db);
    return 0;
    
}

int registration(const char* req, char** res) {
    if(req == NULL)
        return -1;
    sqlite3* db;
    
    struct json_object *jobj = json_tokener_parse(req);
    struct json_object *jlogin = json_object_object_get(jobj, "login"); 
    struct json_object *jpass = json_object_object_get(jobj, "password");
    struct json_object *jfname = json_object_object_get(jobj, "first_name"); 
    struct json_object *jlname = json_object_object_get(jobj, "last_name");
    t_user user;
    strcpy(user.login, json_object_get_string(jlogin));
    strcpy(user.password, json_object_get_string(jpass));
    strcpy(user.first_name, json_object_get_string(jfname));
    strcpy(user.last_name, json_object_get_string(jlname));
    mx_memset(&user.file_name, 0, sizeof(user.file_name));
    user.size = 0;

    mx_openDB(DATABASE_NAME, &db);
    int id = mx_insert_user(db, &user, NULL);
    if(id < 0) {
        *res =  mx_create_err_res("Registration error;");
        return -1;
    }
    struct json_object *juser_id = json_object_new_int(id);
    json_object_object_add(jobj, "user_id", juser_id);
    const char *json_str = json_object_to_json_string(jobj);
    *res =  mx_strdup((char*)json_str);
    sqlite3_close(db);
    return 0;
    
}
