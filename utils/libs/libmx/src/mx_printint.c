#include "../inc/libmx.h"

void mx_printint(int n) {
    long int num = n;
    long int dod = 1;

    if (num < 0) {
        mx_printchar('-');
        num = -num;
    }
    while (num / dod > 0)
        dod *= 10;
    dod /= 10;
    if (dod == 0)
        mx_printchar('0');
    while (dod > 0) {
        mx_printchar(num / dod + '0');
        num %= dod;
        dod /= 10;
    }
} 

// int main() {
//     int a = -1;

//     mx_printint(a);

//     return 0;
// }
