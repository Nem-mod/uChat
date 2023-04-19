#include "../inc/libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;

    char *str1 = mx_strdup(s1);
    char *str2 = mx_strdup(s2);
    char *res = mx_strnew(mx_strlen(str1) + mx_strlen(str2));
    
    mx_strcpy(res, str1);
    mx_strcat(res, str2);
    mx_strdel(&str1);
    mx_strdel(&str2);
    
    return res;
}

// int main() {
//     char s1[] = "Hello";
//     char s2[] = "World";

//     printf("%s\n", mx_strjoin(s1, s2));
//     printf("%s\n", mx_strjoin(NULL, s2));
//     printf("%s\n", mx_strjoin(s1, NULL));
//     printf("%s\n", mx_strjoin(NULL, NULL));

//     return 0;
// }
