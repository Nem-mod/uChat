#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    int start = 0;
    int end = 0;
    char *res = NULL;
    int len = 0;
    
    if (str == NULL)
        return NULL;
    for (int i = 0; mx_isspace(str[i]); i++)
        start++;
    end = mx_strlen(str) - 1;
    for (int i = end; mx_isspace(str[i]); i--)
        end--;
    end++;
    len = end - start;
    res = mx_strnew(len);

    return mx_strncpy(res, &str[start], len);
}

// int main() {
//     // char str[] = "         Hello world           ";
//     char str[] = "                    ";

//     printf("%s", mx_strtrim(str));

//     return 0;
// }

