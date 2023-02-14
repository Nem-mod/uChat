#include "libdb.h"

void mx_create_contacts_table(sqlite3 *db) {
    char* sql = "CREATE TABLE IF NOT EXISTS CONTACTS(" \
        "CONTACT_ID      INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
        "USER_ID         INTEGER         NOT NULL," \
        "USER_CONTACT_ID INTEGER         NOT NULL," \
        "CONSTRAINT FK_USERS \
            FOREIGN KEY (USER_ID) \
            REFERENCES USERS(USER_ID))";
    mx_create_table(db, sql, mx_callback);
}