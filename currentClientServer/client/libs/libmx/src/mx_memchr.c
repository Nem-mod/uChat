#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    char *ps = (char *)s;

    for (size_t i = 0; i < n; i++)
        if (ps[i] == (char)c)
            return &ps[i];
    return NULL;
}

// int main() {
//     char s[] = "Hello world";

//     printf("%s\n", mx_memchr(s, 'w', 11));
//     printf("%s\n", mx_memchr(s, 'l', 11));
//     printf("%s\n", mx_memchr(s, 'z', 11));

//     return 0;
// }
