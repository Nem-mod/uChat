
#include "libdb.h"

int mx_insert_group_member(sqlite3* db, t_group* group, t_user* user){
    char sql[255];
    int last_row_id = 0;
    sprintf(sql, "INSERT INTO GROUP_MEMBERS(GROUP_ID, USER_ID)"  \
    "VALUES(\"%d\", \"%d\");",
    group->group_id, user->user_id);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}
