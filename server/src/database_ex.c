#include "server.h"

int mx_delete_data(sqlite3* db, char* from, char* spec) {
    char sql[365];
    sprintf(sql, "DELETE FROM  %s " \
        "WHERE %s;",
        from, spec
    );
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0; 
}

static int select_callback(void * param, int argc, char **argv, char **azColName)
{
    json_object *obj = json_object_new_object();
    for (int i = 0; i < argc; i++) {
        if(argv[i] == NULL) {
            continue;
        }
        json_object *val = json_object_new_string(argv[i]);
        json_object_object_add(obj, azColName[i], val);
    }
    json_object_array_add((json_object *) param, obj);
    return 0;
}
int mx_select_data(sqlite3* db, char* from, char* columns, json_object* sqlout) {
    char sql[365];
    sprintf(sql, "SELECT %s " \
        "FROM %s;",
        columns, from
    );
    int rt = sqlite3_exec(db, sql, select_callback, sqlout, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0; 
}

int mx_update_data(sqlite3* db, char* from , char* spec, char* newData, char* sqlout) {
    char sql[365];
    sprintf(sql, "UPDATE    %s " \
        "SET   %s "
        "WHERE  %s;",
        from, newData, spec
    );
    int rt = sqlite3_exec(db, sql, mx_callback, sqlout, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0; 
}
