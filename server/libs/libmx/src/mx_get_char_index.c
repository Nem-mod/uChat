#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL)
        return -2;
    for (int i = 0; str[i] != '\0'; i++)
        if(c == str[i])
            return i;
    return -1; 
}

// int main() {
//     char str1[] = "Hello World Lorem ipsum";
//     char *str2 = NULL;

//     printf("%d\n", mx_get_char_index(str1, 'm'));
//     printf("%d\n", mx_get_char_index(str1, 'z'));
//     printf("%d\n", mx_get_char_index(str2, 'a'));

//     return 0;
// }
