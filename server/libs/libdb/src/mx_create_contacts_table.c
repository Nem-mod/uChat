#include "libdb.h"

void mx_create_contacts_table(sqlite3 *db) {
    char* tmp = "CREATE TABLE IF NOT EXISTS CONTACTS(" \
        "CONTACT_ID     INTEGER         NOT NULL," \
        "USER_ID        INTEGER         NOT NULL," \
        "PRIMARY KEY    (CONTACT_ID, USER_ID)," \
        "CONSTRAINT FK_USERS \
            FOREIGN KEY (USER_ID) \
            REFERENCES USERS(USER_ID))";
    mx_create_table(db, tmp, mx_callback);
}
