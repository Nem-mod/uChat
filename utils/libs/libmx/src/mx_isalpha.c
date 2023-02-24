#include "../inc/libmx.h"

bool mx_isalpha(int c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return true;
    return false;
}

// int main() {
//     printf("%d", mx_isalpha('G'));
//     printf("%d", mx_isalpha('1'));

//     return 0;
// }
