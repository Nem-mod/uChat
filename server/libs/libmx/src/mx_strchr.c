#include "../inc/libmx.h"

char *mx_strchr(const char *s, int c) {
    int index = mx_get_char_index(s, c);

    if (index >= 0)
        return (char*)&s[index];
    return NULL;
}

// int main() {
//     char s[] = "Hello world";

//     printf("%s\n", mx_strchr(s, 'w'));
//     printf("%s\n", mx_strchr(s, 'H'));
//     printf("%s\n", mx_strchr(s, 'd'));
//     printf("%s\n", mx_strchr(s, 'z'));

//     return 0;
// }
