#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *list, bool(*cmp)(void *a, void *b)) {
    if (list == NULL || list->next == NULL || cmp == NULL)
        return list;
    
    int count = 0;
    t_list *current = list;
    
    while (current != NULL) {
        current = current->next;
        count++;
    }
    
    for (int i = 0; i < count - 1; i++) {
        current = list;
        for (int x = 0; x < count - 1; x++) {
            if (cmp(current->data, current->next->data)) {
                void *temp_data = current->data;
                current->data = current->next->data;
                current->next->data = temp_data;
                
            }
            current = current->next;
        }
    }
    
    return list;
}

// bool cmp(void *a, void *b) {
//     if ((int)a > (int)b)
//         return true;
//     return false;
// }

// int main() {
//     t_list *list = malloc(sizeof(*list));
//     list->data = (void*)3;
//     list->next = malloc(sizeof(list->next));
//     list->next->data = (void*)1;
//     list->next->next = malloc(sizeof(list->next->next));
//     list->next->next->data = (void*)2;
//     list->next->next->next = NULL;
    
//     printf("%d\n", (int)list->data);
//     printf("%d\n", (int)list->next->data);
//     printf("%d\n\n", (int)list->next->next->data);
//     //printf("%d\n\n", mx_list_size(list));
    
//     mx_sort_list(list, &cmp);
//     printf("%d\n", (int)list->data);
//     printf("%d\n", (int)list->next->data);
//     printf("%d\n\n", (int)list->next->next->data);
    
    
//     return 0;
// } 
