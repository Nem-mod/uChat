#include "db_utils.h"
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
    if (rc != SQLITE_OK)
        fprintf(stderr, "error: %s\n", sqlite3_errmsg(db));
}

void mx_create_users_table(sqlite3 *db) {
    char* sql = "CREATE TABLE IF NOT EXISTS USERS(" \
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "login          VARCHAR(32)     NOT NULL UNIQUE," \
        "password       VARCHAR(18)     NOT NULL," \
        "nick_name      VARCHAR(64)     NOT NULL," \
        "first_name     VARCHAR(64)     NOT NULL," \
        "last_name      VARCHAR(64)     NOT NULL," \
        "user_token      VARCHAR(255)     NOT NULL," \
        "file_size      UNSIGNED BIG INT," \
        "file_name  VARCHAR(255))";
    mx_create_table(db, sql, mx_callback);
}

void mx_create_contacts_table(sqlite3 *db) {
    char* sql = "CREATE TABLE IF NOT EXISTS CONTACTS(" \
        "contact_id      INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," \
        "user_id         INTEGER         NOT NULL," \
        "user_contact_id INTEGER         NOT NULL," \
        "FOREIGN KEY(user_id) REFERENCES users(id)," \
        "FOREIGN KEY(user_contact_id) REFERENCES users(id)," \
        "UNIQUE(user_id, user_contact_id),"\
        "CHECK(user_id > user_contact_id));";
    mx_create_table(db, sql, mx_callback);
}

void mx_create_groups_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS GROUPS(" \
        "group_id      INTEGER PRIMARY KEY AUTOINCREMENT," \
        "group_name    VARCHAR(64)         NOT NULL," \
        "group_privacy INT                NOT NULL," \
        "file_size     UNSIGNED            BIG INT," \
        "file_name  VARCHAR(255))";

    mx_create_table(db, sql, mx_callback); 
}

void mx_create_group_members_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS GROUP_MEMBERS(" \
        "group_member_id INTEGER PRIMARY KEY AUTOINCREMENT  NOT NULL," \
        "group_id     INTEGER       NOT NULL," \
        "user_id      INTEGER       NOT NULL," \
        "CONSTRAINT FK1_GROUP_USERS \
            FOREIGN KEY (group_id) \
            REFERENCES GROUPS(group_id)" \
        "CONSTRAINT FK2_GROUP_USERS \
            FOREIGN KEY (user_id) \
            REFERENCES USERS(user_id))";
    mx_create_table(db, sql, mx_callback);
}

void mx_create_messages_table(sqlite3* db) {
    char* sql = "CREATE TABLE IF NOT EXISTS MESSAGES(" \
        "message_id     INTEGER PRIMARY KEY     NOT NULL,"
        "group_id       INTEGER     NOT NULL," \
        "user_id        INTEGER     NOT NULL," \
        "user_nick_name VARCHAR(64)     NOT NULL," \
        "message_text   TEXT        NOT NULL," \
        "sent_datatime  TEXT        NOT NULL," \
        "file_name   VARCHAR(225)," \
        "file_size      UNSIGNED BIG INT,"
        "CONSTRAINT FK1_MESSAGES \
            FOREIGN KEY (group_id) \
            REFERENCES GROUPS(group_id)" \
        "CONSTRAINT FK2_MESSAGES \
            FOREIGN KEY (user_id) \
            REFERENCES USERS(user_id))";

    mx_create_table(db, sql, mx_callback);
}

/*====================Insert====================*/

char* create_token(int length) {\
    int seed = 2454193;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t stringLen = strlen(string);
    char *randomString = NULL;

    srand(length + ++seed);
    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length + 1));

    short key = 0;
    for (int n = 0;n < length;n++) {
        key = rand() % stringLen;
        randomString[n] = string[key];
    }

    randomString[length] = '\0';
    return randomString;
}

int mx_insert_user(sqlite3* db, t_user* data, char** errMsg) {
    char sql[255];
    int last_row_id = 0;
    char* token = create_token(strlen(data->login) * 3);

    if(data->size != 0) {
        sprintf(sql, "INSERT INTO USERS(login, password, nick_name, first_name, last_name, user_token, file_name, file_size)"  \
        "VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%d\");",
        data->login, data->password, 
        data->login, data->first_name, 
        data->last_name, token,
        data->file_name, data->size);
    } else {
        sprintf(sql, "INSERT INTO USERS(login, password, nick_name, first_name, last_name, user_token)"  \
        "VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");",
        data->login, data->password, 
        data->login, data->first_name, 
        data->last_name, token);
    }
    
    
    int rt = sqlite3_exec(db, sql, mx_callback, 0, errMsg);
    if( rt != SQLITE_OK){
        return -1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

int mx_insert_contact(sqlite3* db, int user_id, int contact_user_id){
    if(user_id == contact_user_id || contact_user_id == 0) {
        return -1;
    }
    
    if(user_id < contact_user_id) {
        int tmp = contact_user_id;
        contact_user_id = user_id;
        user_id = tmp;
    }
    char sql[255];
    sprintf(sql, "INSERT INTO CONTACTS(user_id, user_contact_id)"  \
    "VALUES(\'%d\', \'%d\');",
    user_id, contact_user_id);
    char* err;
    int rt = sqlite3_exec(db, sql, mx_callback, 0, &err);
    if( rt != SQLITE_OK){
        return -1;
    }

    return 0;
}

int mx_insert_group(sqlite3* db, t_group* data){
    char sql[255];
    int last_row_id = 0;
   
    
    sprintf(sql, "INSERT INTO GROUPS(group_name, group_privacy)"  \
    "VALUES(\"%s\",\"%d\");",
    data->group_name, data->privacy);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return -1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

int mx_insert_group_member(sqlite3* db, t_group* group, t_user* user){
    char sql[255];
    int last_row_id = 0;
    sprintf(sql, "INSERT INTO GROUP_MEMBERS(group_id, user_id)"  \
    "VALUES(\"%d\", \"%d\");",
    group->group_id, user->user_id);
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return -1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

int mx_insert_message(sqlite3* db, t_message* message) {
    
    char sql[255];
    int last_row_id = 0;
    if(message->file_name[0] != 0) {
        sprintf(sql, "INSERT INTO MESSAGES(group_id, user_id, user_nick_name, message_text, sent_datatime, file_name, file_size)"  \
            "VALUES(\"%d\", \"%d\",  \"%s\", \"%s\", \"%s\", \"%s\", \"%d\");",
            message->group_id, message->user_id, message->user_nick_name, message->message_text,
            message->sent_datatime, message->file_name, message->size);

    } else {
        sprintf(sql, "INSERT INTO MESSAGES(group_id, user_id, user_nick_name, message_text, sent_datatime)"  \
            "VALUES(\"%d\", \"%d\",  \"%s\", \"%s\", \"%s\");",
            message->group_id, message->user_id, message->user_nick_name, message->message_text, message->sent_datatime);
    }
    int rt = sqlite3_exec(db, sql, mx_callback, 0, NULL);
    if( rt != SQLITE_OK){
        return -1;
    }
    last_row_id = sqlite3_last_insert_rowid(db);
    return last_row_id;
}

