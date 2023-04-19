#include "../inc/libmx.h"

bool mx_isupper(int c) {
    if (c >= 65 && c <= 90)
        return true;
    return false;
}

// int main() {
//     printf("%d", mx_isupper('A'));
//     printf("%d", mx_isupper('y'));

//     return 0;
// }
