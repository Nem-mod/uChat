#pragma once

#include <stdio.h>

#include <unistd.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <malloc.h>             // for Linux -> malloc_usable_size
// #include <malloc/malloc.h>      // for MacOS -> malloc_size

typedef struct s_list {
    void *data;
    struct s_list *next;
}       t_list;


/*
**********PRINT_PACK**********
*/
void mx_printerr(const char *s);
void mx_printchar(char c);
void mx_print_unicode(wchar_t c);
void mx_printstr(const char* s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int n);

/*
**********MATH_PACK**********
*/
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);

/*
**********BOOL_PACK**********
*/
bool mx_isalpha(int c);
bool mx_isdigit(int c);
bool mx_islower(int c);
bool mx_isupper(int c);
bool mx_isspace(int c);

/*
**********OTHER_PACK**********
*/
unsigned long mx_hex_to_nbr(const char *hex);
char *mx_nbr_to_hex(unsigned long nbr);
int mx_intlen(int num);

/*
**********ALGO_PACK**********
*/
void mx_foreach(const int *arr, int size, void(*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);

/*
**********STRING_PACK**********
*/
char *mx_strnew(const int size);
char *mx_itoa(int number);
int mx_atoi(const char *str);
void mx_strpswap(char **a, char **b);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
bool mx_str_isalpha(char *str);
bool mx_str_isdigit(char *str);
int mx_strlen(const char* s);
char *mx_strcpy(char *dst, const char *src);
char *mx_strdup(const char *str);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strndup(const char *s1, size_t n);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strncat(char *restrict s1, const char *restrict s2, int len);
char *mx_strchr(const char *s, int c);
int mx_strcmp(const char *s1, const char *s2);
int mx_strncmp(const char *s1, const char *s2, int n);
int mx_get_substr_index(const char *str, const char *sub);
char *mx_strstr(const char *s1, const char *s2);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char delimiter);
char *mx_strtrim(const char *str);
char *mx_del_extra_spaces(const char*str);
char **mx_strsplit(char const *s, char c);
char *mx_strjoin(char const *s1, char const *s2);
char *mx_file_to_str(const char *filename);
int mx_file_len(const char *filename);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);

/*
**********MEM_PACK**********
*/
void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little,size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

/*
**********LIST_PACK**********
*/
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **list);
void mx_pop_back(t_list **list);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *list, bool(*cmp)(void *a, void *b));
int mx_listcmp(t_list *l1, t_list *l2);
