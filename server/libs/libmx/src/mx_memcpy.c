#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *pdst = (char*) dst;
    char *psrc = (char*) src;


    for (size_t i = 0; i < n; i++)
        pdst[i] = psrc[i];

    return dst;
}
