#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL || replace == NULL)
        return NULL;

    int str_len = mx_strlen(str);
    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    int res_len = str_len - mx_count_substr(str, sub) * (sub_len - replace_len);
    
    char *res = mx_strnew(res_len);
    int start = 0;

    while (true) {
        int substr_index = mx_get_substr_index(&str[start], sub);

        if (substr_index < 0)
            substr_index = str_len;
        mx_strncat(res, &str[start], substr_index);
        if (substr_index == str_len)
            break;
        mx_strcat(res, replace);
        start = start + substr_index + sub_len;
    }

    return res;
}

// int main() {

//     printf("%s\n", mx_replace_substr("Mcdonalds", "don", "br"));
//     printf("%s\n", mx_replace_substr("Mcdonalds", "Mcdonalds", "aa"));
//     printf("%s\n", mx_replace_substr("Ururu turu", "ru", "ta"));

//     return 0;
// }
