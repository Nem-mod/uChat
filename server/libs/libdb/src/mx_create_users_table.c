#include "libdb.h"

void mx_create_users_table(sqlite3 *db) {
    char* tmp = "CREATE TABLE IF NOT EXISTS USERS(" \
        "USER_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "LOGIN          VARCHAR(20)     NOT NULL," \
        "PASSWORD       VARCHAR(18)     NOT NULL," \
        "NICK_NAME      VARCHAR(40)     NOT NULL," \
        "FIRST_NAME     VARCHAR(30)     NOT NULL," \
        "LAST_NAME      VARCHAR(30)     NOT NULL," \
        "PROFILE_PHOTO  BLOB)";
    mx_create_table(db, tmp, mx_callback);
}
