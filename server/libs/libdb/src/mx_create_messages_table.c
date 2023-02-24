#include "libdb.h"

void mx_create_messages_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS MESSAGES(" \
        "MESSAGE_ID     INTEGER PRIMARY KEY     NOT NULL,"
        "GROUP_ID       INTEGER     NOT NULL," \
        "USER_ID        INTEGER     NOT NULL," \
        "MESSAGE_TEXT   TEXT        NOT NULL," \
        "SENT_DATATIME  TEXT        NOT NULL," \
        "MESSAGE_FILE   BLOB," \
        "FILE_SIZE      INTEGER,"
        "CONSTRAINT FK1_MESSAGES \
            FOREIGN KEY (GROUP_ID) \
            REFERENCES GROUPS(GROUP_ID)" \
        "CONSTRAINT FK2_MESSAGES \
            FOREIGN KEY (USER_ID) \
            REFERENCES USERS(USER_ID))";

    mx_create_table(db, sql, mx_callback);
}
