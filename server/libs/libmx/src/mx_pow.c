#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow) {
    double result = 1;
    
    for (unsigned int i = 0; i < pow; i++) {
        result *= n;
    }
    return result;
}

// int main() {
//     printf("%f\n", mx_pow(2.5,3));

//     return 0;
// }
