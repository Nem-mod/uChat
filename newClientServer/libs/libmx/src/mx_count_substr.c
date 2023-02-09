#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int count = -1;
    char *s = (char *)str;
    
    if (sub == NULL || str == NULL)
        return -1;
    if (sub[0] == '\0')
        return 0;
    while (s != NULL) {
        count++;
        s = mx_strstr(s, sub);
        if (s != NULL)
            s = &s[1];
    }
    return count;
}

// int main() {
//     char s1[] = "yo, yo, yo, Neo";

//     printf("%d\n", mx_count_substr(s1, "yo"));
//     printf("%d\n", mx_count_substr(s1, "yoo"));
//     printf("%d\n", mx_count_substr(s1, ""));
//     printf("%d\n", mx_count_substr(s1, NULL));

//     return 0;
// }
