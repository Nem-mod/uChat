#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (list == NULL)
        return;
    if (*list == NULL) {
        *list = mx_create_node(data);
        return;
    }
    
    t_list *current = *list;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    t_list *node = mx_create_node(data);
    current->next = node;
}

// int main() {
//     char str1[] = "Hello";
//     char str2[] = "World";
//     
//     t_list *list = mx_create_node(str1);
//     *list = *list;
//     mx_push_back(&list, str2);
//     printf("%s %s\n", list->data, list->next->data);
//     
//     return 0;
// }
