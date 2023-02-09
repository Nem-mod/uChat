#include "libdb.h"

void mx_create_group_members_table(sqlite3* db) {
    char* tmp = "CREATE TABLE IF NOT EXISTS GROUP_MEMBERS(" \
        "GROUP_ID     INTEGER       NOT NULL," \
        "USER_ID      INTEGER       NOT NULL," \
        "PRIMARY KEY (GROUP_ID, USER_ID)," \
        "CONSTRAINT FK1_GROUP_USERS \
            FOREIGN KEY (GROUP_ID) \
            REFERENCES GROUPS(GROUP_ID)" \
        "CONSTRAINT FK2_GROUP_USERS \
            FOREIGN KEY (USER_ID) \
            REFERENCES USERS(USER_ID))";
    mx_create_table(db, tmp, mx_callback);
}
