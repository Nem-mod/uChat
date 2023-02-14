#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    char *pdst = (char *)dst;
    char *psrc = (char *)src;
    size_t i;

    for (i = 0; i < n; i++) {
        pdst[i] = psrc[i];
        if (psrc[i] == c)
            break;
    }
    if (i == n - 1)
        return NULL;

    return pdst + i + 1;
}

// int main() {
//     char str1[] = "Hello thereZ";
//     char str2[25];
//     char *p = NULL;

//     p = mx_memccpy(str2, str1, 'H', 20);
//     printf("%s\n%s\n", str2, p);

//     return 0;
// }
