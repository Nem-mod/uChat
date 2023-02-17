#include "../inc/libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    int char_count = 0;
    
    if (src != NULL)
        while(src[char_count] != '\0') {
            dst[char_count] = src[char_count];
            char_count++;
        }
    dst[char_count] = '\0';
    
    return dst;
}

// int main() {
//     char str[] = "9heY2n eRgdyCaPIveNcRh4evKQiJCOrUtkxPY2vvtui";
//     char dst[50];

//     printf("%s\n%s\n", str, mx_strcpy(dst, str));

//     return 0;
// }
