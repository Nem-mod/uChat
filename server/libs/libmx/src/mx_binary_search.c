#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int end = size - 1;
    int mid = (start + end) / 2;

    if (arr == NULL || s == NULL || count == NULL)
        return -1;
    while (start <= end) {
        int res = mx_strcmp(s, arr[mid]);

        *count += 1;
        if (res > 0) 
            start = mid + 1;
        else if (res < 0)
            end = mid - 1;
        else
            return mid;
        mid = (start + end) / 2;
    }
    *count = 0;

    return -1;
}

// int main() {
//     char *arr[]= {"222", "Abcd", "aBc", "ab", "az", "z"};
//     int count= 0;

//     printf("%d\n", mx_binary_search(arr, 6, "ab", &count));//returns 3 and count = 3
//     printf("%d\n\n", count);
//     count= 0;
//     printf("%d\n", mx_binary_search(arr, 6, "aBc", &count));  //returns 2 and count = 1
//     printf("%d\n\n", count);
//     count= 0;
//     printf("%d\n", mx_binary_search(arr, 6, "aBz", &count));  //returns -1 and count = 0
//     printf("%d\n\n", count);
// }
