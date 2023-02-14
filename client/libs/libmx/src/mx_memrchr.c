#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *ps = (char *)s;

    if (s == NULL)
        return NULL;
    for (size_t i = n - 1; i >= 0; i--) {
        if (ps[i] == (char)c)
            return &ps[i];   
        if (i == 0)
            break;
    }
    return NULL;
}

// int main() {
//     // char s[] = "Hello world";
//     char *s = NULL;

//     printf("\n%s\n", mx_memrchr(s, 'w', 11));
//     printf("\n%s\n", mx_memrchr(s, 'l', 11));
//     printf("\n%s\n", mx_memrchr(s, 'o', 11));
//     printf("\n%s\n", mx_memrchr(s, 'z', 11));

//     return 0;
// }
