#include "libdb.h"

void mx_create_table (sqlite3 *db, char *sql, int (*callback)(void*, int, char**, char**)) {
    int rc;

    rc = sqlite3_exec(db, sql, callback, 0, NULL);
    // if (rc != SQLITE_OK)
        //fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}