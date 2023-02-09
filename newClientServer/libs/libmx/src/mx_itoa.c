#include "../inc/libmx.h"

char *mx_itoa(int number) {
    long int n = number;
    int isNegative = 0;
    int len = mx_intlen(number);

    if (n < 0) {
        isNegative = 1;
        n = -n;
        len++;
    }
    
    char *str = mx_strnew(len + isNegative);

    if (isNegative == 1)
        str[0] = '-';
    for (int i = len - 1; i >= 0 + isNegative; i--) {
        str[i] = n % 10 + '0';
        n /= 10;
    }

    return str;
}

// int main() {
//     int a = -2147483648;
//     printf("%s", mx_itoa(a));

//     return 0;
// }
