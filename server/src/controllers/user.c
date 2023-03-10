#include "server.h"

int getAll_users(const char* req, char* res) {
    if(req == NULL)
        return 1;
    
    json_object *json =  json_object_new_array();
    sqlite3* db;
    mx_openDB(DATABASE_NAME, &db);
    mx_select_data(db, "USERS", "*", NULL, json);
    const char *json_str = json_object_to_json_string(json);
    mx_strcpy(res, json_str);
    sqlite3_close(db);
    
    return 0;
}
