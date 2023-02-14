#include "libdb.h"

int mx_update_data(sqlite3* db, char* from , char* spec, char* newData, char* sqlout) {
    char sql[365];
    sprintf(sql, "UPDATE    %s " \
        "SET   %s "
        "WHERE  %s;",
        from, newData, spec
    );
    int rt = sqlite3_exec(db, sql, mx_callback, sqlout, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0; 
}