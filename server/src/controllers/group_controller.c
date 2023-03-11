#include "server.h"
int get_group(const char* req, char* res){
    if(req == NULL)
        return 1;
    
    sqlite3* db;
    json_object *json =  json_object_new_array();
    struct json_object *jobj;
    jobj = json_tokener_parse(req);
    struct json_object *jgroup_name = json_object_object_get(jobj, "group_name"); 
    const char* group_name = json_object_get_string(jgroup_name);
  

    mx_openDB(DATABASE_NAME, &db);
    char temp[256];
    sprintf(temp, "group_name = \'%s\' ;",
        group_name
    );
    mx_select_data(db, "GROUPS", "*", temp, json);
    if(res != NULL){
        const char *json_str = json_object_to_json_string(json);
        mx_strcpy(res, json_str);
    }
            
    sqlite3_close(db);
    int group_id = json_object_get_int(json_object_object_get(json, "group_id"));

    return group_id;
}
int create_group(const char* req, char* res){
    if(req == NULL)
        return 1;
    
    sqlite3* db;
    struct json_object *jobj;
    jobj = json_tokener_parse(req);
    struct json_object *jgroup_name = json_object_object_get(jobj, "group_name"); 
    struct json_object *juser_id= json_object_object_get(jobj, "user_id"); 
    t_group group;
    strcpy(group.group_name, json_object_get_string(jgroup_name));

    mx_openDB(DATABASE_NAME, &db);
    group.group_id = mx_insert_group(db, &group);
    mx_insert_group_member(db, &group, json_object_get_int(juser_id));
    const char *json_str = json_object_to_json_string(jobj);
    mx_strcpy(res, json_str);
    sqlite3_close(db);
    
    return 0;
}

int delete_group(const char* req, char* res){
    if(req == NULL)
        return 1;
    
    sqlite3* db;
    
    struct json_object *jobj;
    jobj = json_tokener_parse(req);
    int group_id = get_group(req, NULL);

    mx_openDB(DATABASE_NAME, &db);
    char temp[256];
    sprintf(temp, "group_id = \'%d\'; " ,
        group_id
    );
    mx_delete_data(db, "GROUPS", temp);
    const char *json_str = json_object_to_json_string(jobj);
    mx_strcpy(res, json_str);
    sqlite3_close(db);
    
    return 0;
}

int get_group_members(const char* req, char* res){
    if(req == NULL)
        return 1;
    
    sqlite3* db;
    struct json_object *jobj;
    json_object *json_arr =  json_object_new_array();
    jobj = json_tokener_parse(req);
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
        char json_user_str[256];
        json_object* jarray_obj = json_object_array_get_idx(json_arr, i);
        const char* arr_obj_str = json_object_to_json_string(jarray_obj);
        get_users_by_id(arr_obj_str, json_user_str);
        struct json_object *juser = json_tokener_parse(json_user_str);
        json_object_array_add(json_user_arr, juser);
    }

    const char *group_members_json_str = json_object_to_json_string(json_user_arr);
    mx_strcpy(res, group_members_json_str);
    sqlite3_close(db);
    
    return 0;
}
