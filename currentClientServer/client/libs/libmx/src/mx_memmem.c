#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    char *pbig = (char *)big;
    char *plittle = (char *)little;

    if (big == NULL || little == NULL)
        return NULL;
    if(big_len >= little_len && big_len != 0 && little_len != 0)
        for (size_t i = 0; i < big_len; i++) {
            char *mchr_result = mx_memchr(&pbig[i], plittle[0], big_len);

            if (mchr_result == NULL)
                break;
            if (mx_memcmp(mchr_result, little, little_len) == 0)
                return mchr_result;
        }
    return NULL;
}

// int main() {
//     // char s1[] = "Hello world lorem ipsum";
//     char *s1 = NULL;
    
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 23, "world", 5));
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 23, "ipsum", 5));
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 23, "ld", 2));
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 23, "wworld", 6));
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 23, "worldworldworldworldworldworld", 30));
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 0, "worldworldworldworldworldworld", 30));
//     printf("%s\n%s\n\n", s1, mx_memmem(s1, 23, "worldworldworldworldworldworld", 0));
    

//     return 0;
// }
