#include "../inc/libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    int index = mx_get_substr_index(s1, s2);

    if (index >= 0)
        return (char*)&s1[index];
    return NULL;
}

// int main() {
//     char s1[] = "Hello world lorem ipsum";
    
//     printf("%s\n%s\n\n", s1, mx_strstr(s1, "world"));
//     printf("%s\n%s\n\n", s1, mx_strstr(s1, "ipsum"));
//     printf("%s\n%s\n\n", s1, mx_strstr(s1, "ld"));
//     printf("%s\n%s\n\n", s1, mx_strstr(s1, "wworld"));

//     return 0;
// }
