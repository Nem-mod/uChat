#pragma once

int mx_select_data(sqlite3* db, char* from, char* columns, json_object* sqlout);
int mx_delete_data(sqlite3* db, char* from, char* spec);
int mx_update_data(sqlite3* db, char* from , char* spec, char* newData, char* sqlout);
