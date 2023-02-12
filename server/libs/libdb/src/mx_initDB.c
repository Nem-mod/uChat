#include "libdb.h"

void mx_initDB(sqlite3* db){
    int rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON", mx_callback ,0, NULL);
    mx_create_users_table(db);
    mx_create_contacts_table(db);
    mx_create_groups_table(db);
    mx_create_group_members_table(db);
    mx_create_messages_table(db);
}