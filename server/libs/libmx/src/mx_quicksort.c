#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL)
        return -1;


    int swapCount = 0;
    int l = -1;
    int r = -2;
    int mid = (right - left) / 2 + left;

    while(l != r) {
        for (l = left; l < mid; l++) {
            if (mx_strlen(arr[l]) > mx_strlen(arr[mid]))
                break;
        }
        for (r = right; r > mid; r--) {
            if (mx_strlen(arr[r]) < mx_strlen(arr[mid]))
                break;
        }
        if (l != r) {
            mx_strpswap(&arr[l], &arr[r]);
            swapCount++;
        }
        if (l == mid && r != mid)
            mid = r;
        else
        if (l != mid && r == mid)
            mid = l;
    }
    if (left != mid)
        swapCount += mx_quicksort(arr, left, mid - 1);
    if (right != mid)
        swapCount += mx_quicksort(arr, mid + 1, right);

    return swapCount;
}

// int main () {
//     char *arr[] = {"DMC", "Clint Eastwood", "Dr Brown", "Einstein", "Jessica", "Biff Tannen"};
//     //char *arr[] = {"3..", "14............", "8.......", "8.......", "7......", "11........."}; 
//     // char *arr[] = {"8       ", "7      ", "6     ", "5    "};
//     char d = '*';

//     mx_print_strarr(arr, &d);
//     printf("swaps = %d\n", mx_quicksort(arr, 0, 5));
//     mx_print_strarr(arr, &d);

//     return 0;
// }
