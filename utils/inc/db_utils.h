#pragma once

#include "sqlite3.h"
#include "tables.h"
#include <stdio.h>
#include <string.h>
#include<string.h>
#include <stdlib.h>


void mx_openDB(const char* filename, sqlite3** ppDB);
void mx_initDB(sqlite3* db);
void mx_create_table (sqlite3 *db, char *sql, int (*callback)(void*, int, char**, char**));
void mx_create_users_table(sqlite3 *db);
void mx_create_contacts_table(sqlite3 *db);
void mx_create_groups_table(sqlite3 *db);
void mx_create_group_members_table(sqlite3 *db);
void mx_create_messages_table(sqlite3 *db);
int mx_callback(void *datab, int argc, char **argv, char **azColName);

int mx_insert_user(sqlite3* db, t_user* data);
int mx_insert_contact(sqlite3* db, int user_id, int contact_user_id);
int mx_insert_group(sqlite3* db, t_group* data);
int mx_insert_group_member(sqlite3* db, t_group* group, int user_id);
int mx_insert_message(sqlite3* db, t_group* group, t_group_member* user, t_message* message);

