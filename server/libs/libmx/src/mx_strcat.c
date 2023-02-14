#include "../inc/libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    return mx_strncat(s1, s2, mx_strlen(s2));
}

// int main() {
//     char str1[] = "Hello";
//     char str2[] = "World";

//     mx_strcat(str1, str2);
//     printf("%s\n", str1);

//     return 0;
// }
