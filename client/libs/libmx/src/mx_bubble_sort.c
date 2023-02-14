#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int swap_count = 0;
    
    for (int i = 0; i < size - 1; i++)
        for (int x = i + 1; x < size; x++)
            if (mx_strcmp(arr[i], arr[x]) > 0) {
                char *temp = arr[i];
                
                arr[i] = arr[x];
                arr[x] = temp;
                swap_count++;
            }
    return swap_count;
}
