#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    if (size < 0)
        return NULL;
    
    char *ptr = malloc((size + 1) * sizeof(char));
    
    for (int i = 0; i < size + 1; i++)
        ptr[i] = '\0';
    return ptr;
}
