#include "../inc/libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    int index = 0;
    
    if (arr == NULL || delim == NULL)
        return;
    while(arr[index] != NULL) {
        mx_printstr(arr[index]);
        index++;
        if (arr[index] != NULL)
            mx_printstr(delim);
        else
            mx_printchar('\n');
    }
}

// int main() {
//     char *arr[] ={"Hello", "world", NULL};
//     const char d[] = "*";

//     mx_print_strarr(arr, d);

//     return 0;
// }
