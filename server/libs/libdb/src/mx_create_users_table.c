#include "libdb.h"

void mx_create_users_table(sqlite3 *db) {
    char* sql = "CREATE TABLE IF NOT EXISTS USERS(" \
        "USER_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "LOGIN          VARCHAR(32)     NOT NULL," \
        "PASSWORD       VARCHAR(18)     NOT NULL," \
        "NICK_NAME      VARCHAR(64)     NOT NULL," \
        "FIRST_NAME     VARCHAR(64)     NOT NULL," \
        "LAST_NAME      VARCHAR(64)     NOT NULL," \
        "PROFILE_PHOTO  BLOB)";
    mx_create_table(db, sql, mx_callback);
}
