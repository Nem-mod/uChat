#include "libdb.h"

void mx_create_group_members_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS GROUP_MEMBERS(" \
        "GROUP_MEMBER_ID INTEGER PRIMARY KEY AUTOINCREMENT  NOT NULL," \
        "GROUP_ID     INTEGER       NOT NULL," \
        "USER_ID      INTEGER       NOT NULL," \
        "CONSTRAINT FK1_GROUP_USERS \
            FOREIGN KEY (GROUP_ID) \
            REFERENCES GROUPS(GROUP_ID)" \
        "CONSTRAINT FK2_GROUP_USERS \
            FOREIGN KEY (USER_ID) \
            REFERENCES USERS(USER_ID))";
    mx_create_table(db, sql, mx_callback);
}
