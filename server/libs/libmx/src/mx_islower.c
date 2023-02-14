#include "../inc/libmx.h"

bool mx_islower(int c) {
    if (c >= 97 && c <= 122)
        return true;
    return false;
}

// int main() {
//     printf("%d", mx_islower('A'));
//     printf("%d", mx_islower('y'));

//     return 0;
// }
