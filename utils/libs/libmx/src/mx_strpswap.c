#include "../inc/libmx.h"

void mx_strpswap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// int main() {
//     char *str[] = {"Hello", "world"}; 

//     printf("%s %s\n", str[0], str[1]);
//     mx_swapstr(&str[0], &str[1]);
//     printf("%s %s\n", str[0], str[1]);

//     char *a = "aaa";
//     char *b = "bbb";
//     char **pA = &a;
//     char **pB = &b;

//     printf("%s %s\n", *pA, *pB);
//     mx_swapstr(pA, pB);
//     printf("%s %s\n", *pA, *pB);

//     return 0;
// }
