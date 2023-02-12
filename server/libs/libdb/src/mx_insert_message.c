#include "libdb.h"

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

