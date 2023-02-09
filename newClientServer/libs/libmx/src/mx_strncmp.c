#include "../inc/libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
    for (int i = 0; i < n; i++)
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    return 0;
}

// int main() {
//     char s1[] = "Hello world lorem ipsum";
//     char s2[] = "Hello world pispis";

//     printf("%d\n", mx_strncmp(s1, s2, 5));
//     printf("%d\n", mx_strncmp(s1, s2, 12));
//     printf("%d\n", mx_strncmp(s1, s2, 15));


//     return 0;
// }
