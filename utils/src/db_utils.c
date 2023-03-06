#include "../inc/db_utils.h"

void mx_openDB(const char* filename, sqlite3** ppDB) {
    int rc = sqlite3_open(filename, ppDB);
    
    if(rc){
      sqlite3_close(*ppDB);
      return;
    }
}

void mx_initDB(sqlite3* db){
    // int rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON", mx_callback ,0, NULL); // Unused var
    sqlite3_exec(db, "PRAGMA foreign_keys = ON", mx_callback ,0, NULL);
    mx_create_users_table(db);
    mx_create_contacts_table(db);
    mx_create_groups_table(db);
    mx_create_group_members_table(db);
    mx_create_messages_table(db);
}

int mx_callback(void *datab, int argc, char **argv, char **azColName) {
    (void)datab;
    (void)argc;
    (void)argv;
    (void)azColName;
    return 0;
}

/*====================Create====================*/

void mx_create_table (sqlite3 *db, char *sql, int (*callback)(void*, int, char**, char**)) {
    int rc;

    rc = sqlite3_exec(db, sql, callback, 0, NULL);
    // if (rc != SQLITE_OK)
        //fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}

void mx_create_users_table(sqlite3 *db) {
    char* sql = "CREATE TABLE IF NOT EXISTS USERS(" \
        "USER_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "LOGIN          VARCHAR(20)     NOT NULL," \
        "PASSWORD       VARCHAR(18)     NOT NULL," \
        "NICK_NAME      VARCHAR(40)     NOT NULL," \
        "FIRST_NAME     VARCHAR(30)     NOT NULL," \
        "LAST_NAME      VARCHAR(30)     NOT NULL," \
        "PROFILE_PHOTO  BLOB)";
    mx_create_table(db, sql, mx_callback);
}

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

void mx_create_groups_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS GROUPS(" \
        "GROUP_ID     INTEGER PRIMARY KEY AUTOINCREMENT," \
        "GROUP_NAME   VARCHAR(30)         NOT NULL)";

    mx_create_table(db, sql, mx_callback); 
}

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

/*====================Insert====================*/

int mx_insert_user(sqlite3* db, t_user* data) {
    char sql[255];
    int last_row_id = 0;
    
    sprintf(sql, "INSERT INTO USERS(LOGIN, PASSWORD, NICK_NAME, FIRST_NAME, LAST_NAME)"  \
    "VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\");",
    data->login, data->password, 
    data->nick_name, data->first_name, data->last_name);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

int mx_insert_contact(sqlite3* db, t_user* user, t_user* contact_user){
    char sql[255];
    sprintf(sql, "INSERT INTO CONTACTS(USER_ID, USER_CONTACT_ID)"  \
    "VALUES(\"%d\", \"%d\");",
    user->user_id, contact_user->user_id);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    return 0;
}

int mx_insert_group(sqlite3* db, t_group* data){
    char sql[255];
    int last_row_id = 0;
    sprintf(sql, "INSERT INTO GROUPS(GROUP_NAME)"  \
    "VALUES(\"%s\");",
    data->group_name);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

int mx_insert_group_member(sqlite3* db, t_group* group, t_user* user){
    char sql[255];
    int last_row_id = 0;
    sprintf(sql, "INSERT INTO GROUP_MEMBERS(GROUP_ID, USER_ID)"  \
    "VALUES(\"%d\", \"%d\");",
    group->group_id, user->user_id);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

int mx_insert_message(sqlite3* db, t_group* group, t_group_member* group_member, t_message* message) {
    char sql[255];
    int last_row_id = 0;
    sprintf(sql, "INSERT INTO MESSAGES(GROUP_ID, USER_ID, MESSAGE_TEXT, SENT_DATATIME)"  \
    "VALUES(\"%d\", \"%d\", \"%s\", \"%s\");",
    group->group_id, group_member->user_id, message->message_text, message->sent_datatime);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return 1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

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
