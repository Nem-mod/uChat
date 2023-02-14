#include "../inc/libmx.h"

int mx_count_words(const char *str, char delimiter) {
    int char_count = 0;
    int words_count = 0;
    
    if (str == NULL)
        return 0;
    while (str[char_count] != '\0') {
        char_count++;
        if ((str[char_count] == delimiter || str[char_count] == '\0') && str[char_count - 1] != delimiter)
            words_count++;
    }
    
    return words_count;
}

// int main() {
//     // char str[] = "Hello   * World *** Lorem* ipsum **";
//     // char str[]= "";
//     char *str = NULL;

//     printf("%d\n", mx_count_words(str, '*'));

//     return 0;
// }
