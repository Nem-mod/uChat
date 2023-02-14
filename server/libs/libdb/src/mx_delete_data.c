#include "libdb.h"

int mx_delete_data(sqlite3* db, char* from, char* spec) {
    char sql[365];
    sprintf(sql, "DELETE FROM  %s " \
        "WHERE %s;",
        from, spec
    );
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0; 
}