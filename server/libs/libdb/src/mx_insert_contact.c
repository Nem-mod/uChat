#include "libdb.h"

int mx_insert_contact(sqlite3* db, t_user* user, t_user* contact_user){
    char sql[255];
    sprintf(sql, "INSERT INTO CONTACTS(USER_ID, USER_CONTACT_ID)"  \
    "VALUES(\"%d\", \"%d\");",
    user->user_id, contact_user->user_id);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0;
}