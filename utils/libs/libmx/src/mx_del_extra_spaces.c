#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL)
        return NULL;

    char *tstr = mx_strtrim(str);
    int len = mx_strlen(tstr);
    char *res = mx_strnew(len); 
    bool is_space = false;

    for (int i = 0; i < len; i++) {
        if (!mx_isspace(tstr[i]) && is_space) {
            mx_strncat(res, " ", 1);
            is_space = false;
        }
        if (!mx_isspace(tstr[i])) {
            mx_strncat(res, &tstr[i], 1);
        }
        else {
            is_space = true;
        }
    }
    return res;
}

// int main() {
//     char str[] = "\f My name...    is    \r    Neo     \t  \n";
//     printf("%s", mx_del_extra_spaces(str));

//     return 0;
// }
