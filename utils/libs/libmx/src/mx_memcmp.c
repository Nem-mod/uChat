#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *ps1 = (char *)s1;
    char *ps2 = (char *)s2;

    for (size_t i = 0; i < n; i++)
        if (ps1[i] != ps2[i])
            return ps1[i] - ps2[i];
    return 0;
}

// int main() {
//     char s1[] = "Hfllo world";
//     char s2[] = "Hello world";

//     printf("%d\n", mx_memcmp(s1, s2, mx_strlen(s1)));

//     return 0;
// }
