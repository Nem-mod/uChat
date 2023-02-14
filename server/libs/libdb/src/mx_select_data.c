#include "libdb.h"
static int select_callback(void * param, int argc, char **argv, char **azColName)
{
    int i;
    if(argc == 0) return 0;
    char temp[256];
    for (i = 0; i < argc; i++)
    {
        sprintf(temp, "%s = %s;", azColName[i], argv[i]);
        strcat(param, temp);
    }
    return 0;
}
int mx_select_data(sqlite3* db, char* from, char* columns, char* sqlout) {
    char sql[365];
    sprintf(sql, "SELECT %s " \
        "FROM %s;",
        columns, from
    );
    int rt = sqlite3_exec(db, sql, select_callback, sqlout, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0; 
}