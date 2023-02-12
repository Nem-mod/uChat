#include "libdb.h"

int mx_insert_user(sqlite3* db, t_user* data) {
    char sql[255];
    int last_row_id = 0;
    
    sprintf(sql, "INSERT INTO USERS(LOGIN, PASSWORD, NICK_NAME, FIRST_NAME, LAST_NAME)"  \
    "VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\");",
    data->login, data->password, 
    data->nick_name, data->first_name, data->last_name);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

