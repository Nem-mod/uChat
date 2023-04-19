#include "../inc/libmx.h"

bool mx_isdigit(int c) {
    if (c >= 48 && c <= 57)
        return true;
    return false;
}

// int main() {
//     printf("%d", mx_isdigit('1'));
//     printf("%d", mx_isdigit('a'));

//     return 0;
// }
