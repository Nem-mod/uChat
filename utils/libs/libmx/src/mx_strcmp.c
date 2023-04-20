#include "../inc/libmx.h"

int mx_strcmp(const char *s1, const char *s2) {

    if(s1 == NULL || s2 == NULL)
        return 1;
    int char_count = 0;
    
    while (s1[char_count] != '\0' || s2[char_count] != '\0') {
        if (s1[char_count] - s2[char_count] != 0)
            return s1[char_count] - s2[char_count];
        char_count++;
    }
    return 0;
}
