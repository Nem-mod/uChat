#include "../inc/libmx.h"

int mx_intlen(int num) {
    int len = 0;
    long int n = num;

    if (n < 0)
        n = -n;
    while(n > 0) {
        n /= 10;
        len++;
    }
    if (len == 0)
        len++;
    return len;
}

// int main() {
//     int a = -246345;
//     printf("%d", mx_intlen(a));

//     return 0;
// }
