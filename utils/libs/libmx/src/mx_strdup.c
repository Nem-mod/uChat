#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    if (str == NULL)
        return NULL;
    
    char *ptr = mx_strnew(mx_strlen(str));
    mx_strcpy(ptr, str);

    return ptr;
}

// int main() {
//     char str1[] = "Hello World!";

//     printf("%s\n%s\n", str1, mx_strdup(str1));

//     return 0;
// }
