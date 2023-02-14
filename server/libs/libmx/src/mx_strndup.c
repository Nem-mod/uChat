#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);

    if (s1 == NULL)
        return NULL;
    if (n > len)
        n = len;
    
    char *ptr = mx_strnew(n);

    mx_strncpy(ptr, s1, n);

    return ptr;
}

// int main() {
//     char str[] = "Hello World";

//     printf("%s\n%s\n%s\n", str, mx_strndup(str, 3));

//     return 0;
// }
