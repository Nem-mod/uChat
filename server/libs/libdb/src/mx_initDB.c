#include "libdb.h"

void mx_initDB(){
    char* db_name = "uchat.db";
    sqlite3* db;
    mx_openDB(db_name, &db);
    int rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON", mx_callback ,0, NULL);
    mx_create_users_table(db);
    mx_create_contacts_table(db);
    mx_create_groups_table(db);
    mx_create_group_members_table(db);
    mx_create_messages_table(db);
}