#include "../inc/libmx.h"

char *mx_strncat(char *restrict s1, const char *restrict s2, int len) {
    int s1_length = mx_strlen(s1);
    int s2_length = mx_strlen(s2);
    
    if (s1 == NULL && s2 == NULL)
        return NULL;
    if (s1 == NULL)
        return (char*)s2;
    if (s2 == NULL)
        return s1;

    if (len < 0 || len > s2_length)
        len = s2_length;
    for (int i = 0; i < len; i++) {
        s1[s1_length + i] = s2[i];
    }
    s1[s1_length + len] = '\0';
    
    return s1;
}

// int main() {
//     char str1[] = "Hello";
//     char str2[] = "World";

//     mx_strncat(str1, str2, 3);
//     printf("%s\n", str1);

//     return 0;
// }
