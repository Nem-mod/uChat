#pragma once


int getAll_users(const char* req, char** res); 
int get_users_by_name(const char* req, char** res); 
int get_users_by_id(const char* req, char** res);

int add_contact(const char* req, char** res); 

int get_group(const char* req, char** res);
int create_group(const char* req, char** res);
int delete_group(const char* req, char** res);
int get_group_members(const char* req, char** res);
int insert_group_members(const char* req, char** res);
int add_group_members(const char* req, char** res);

int get_messages(const char* req, char** res);
int create_message(const char* req, char** res);

int login(const char* req, char** res);
int registration(const char* req, char** res);
// char* get_user(sqlite3 db);

// char* post_user(sqlite3 db);
