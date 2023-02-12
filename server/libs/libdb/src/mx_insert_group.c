
#include "libdb.h"

int mx_insert_group(sqlite3* db, t_group* data){
    char sql[255];
    int last_row_id = 0;
    sprintf(sql, "INSERT INTO GROUPS(GROUP_NAME)"  \
    "VALUES(\"%s\");",
    data->group_name);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}
