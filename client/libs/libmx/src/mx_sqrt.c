#include "../inc/libmx.h"

int mx_sqrt(int x) {
    if (x < 0)
        return 0;
    for (int i = 0; i <= x / 2; i++) {
        if (i * i == x)
            return i;
        if (i * i > x)
            return 0;
    }
    return 0;
}

// int main() {
//     printf("%d\n", mx_sqrt(4));
//     printf("%d\n", mx_sqrt(3));

//     return 0;
// }
