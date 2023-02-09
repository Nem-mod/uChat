#include "../inc/libmx.h"

bool mx_str_isalpha(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if(!mx_isalpha(str[i]))
            return false;
    return true;
}

// int main() {
//     printf("%d\n", mx_str_isalpha("H"));

//     return 0;
// }
