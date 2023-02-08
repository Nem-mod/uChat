#include "../inc/libmx.h"

char **mx_strsplit(char const *s, char c) {
    if (s == NULL)
        return NULL;
    
    char **arr = (char**)malloc((mx_count_words(s, c) + 1) * sizeof(char*));
    int word_len = 0;
    int arr_count = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != c)
            word_len++;
        if (i > 0 && s[i - 1] != c && s[i] == c) {
            arr[arr_count] = mx_strndup(&s[i - word_len], word_len);
            word_len = 0;
            arr_count++;
        }
    }
    if (word_len != 0) {
        arr[arr_count] = mx_strdup(&s[mx_strlen(s) - word_len]);
        arr_count++;
    }
    arr[arr_count] = NULL;

    return arr;
}

// int main() {
//     char str[] = "Greenland-Bananal-8";
//     char **arr = mx_strsplit(str, '-');

//     for (int i = 0; arr[i] != NULL; i++)
//         printf("%s\n", arr[i]);

//     return 0;
// }
