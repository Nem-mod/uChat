#include "libdb.h"

void mx_create_groups_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS GROUPS(" \
        "GROUP_ID     INTEGER PRIMARY KEY AUTOINCREMENT," \
        "GROUP_NAME   VARCHAR(64)         NOT NULL)";

    mx_create_table(db, sql, mx_callback); 
}
