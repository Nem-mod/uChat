#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

void mx_openDB(const char* filename, sqlite3** ppDB);
void mx_initDB();
void mx_create_table (sqlite3 *db, char *sql, int (*callback)(void*, int, char**, char**));
void mx_create_users_table(sqlite3 *db);
void mx_create_contacts_table(sqlite3 *db);
void mx_create_groups_table(sqlite3 *db);
void mx_create_group_members_table(sqlite3 *db);
void mx_create_messages_table(sqlite3 *db);
int mx_callback(void *datab, int argc, char **argv, char **azColName);
