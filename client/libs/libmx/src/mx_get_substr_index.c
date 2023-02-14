#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int sub_len = mx_strlen(sub);
    
    if (str == NULL || sub == NULL)
        return -2;
    for (int i = 0; i < mx_strlen(str); i++) {
        int chr_index = mx_get_char_index(&str[i], sub[0]);

        if (mx_strncmp(&str[chr_index + i], sub, sub_len) == 0)
            return chr_index + i;
    }
    return -1;
}

// int main() {
//     char s1[] = "Hello world lorem ipsum";
    
//     printf("%s\n%d\n\n", s1, mx_get_substr_index(s1, "world"));
//     printf("%s\n%d\n\n", s1, mx_get_substr_index(s1, "ipsum"));
//     printf("%s\n%d\n\n", s1, mx_get_substr_index(s1, "ld"));
//     printf("%s\n%d\n\n", s1, mx_get_substr_index(s1, "wworld"));
//     printf("%s\n%d\n\n", s1, mx_get_substr_index(NULL, "wworld"));
//     printf("%s\n%d\n\n", s1, mx_get_substr_index(s1, NULL));

//     return 0;
// }
