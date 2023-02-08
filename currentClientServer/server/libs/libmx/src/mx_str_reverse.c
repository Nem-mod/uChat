#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    int len = mx_strlen(s);

    if (s != NULL)
        for (int i = 0; i < len / 2; i++)
            mx_swap_char(&(s[i]), &(s[len - i - 1]));
}

// int main() {
//     char str[] = "Hello World";

//     mx_str_reverse(str);
//     printf("%s\n", str);

//     return 0;
// }
