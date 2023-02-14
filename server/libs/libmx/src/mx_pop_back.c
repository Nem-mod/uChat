#include "../inc/libmx.h"

void mx_pop_back(t_list **list) {
    t_list *current = *list;
    
    if (list == NULL || *list == NULL)
        return;
    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
        return;
    }
    while (current && current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

// int main() {
//     t_list *list = malloc(sizeof(*list));
//     list->data = "Hello";
//     list->next = malloc(sizeof(list->next));
//     list->next->next = NULL;
//     list->next->data = "World";
    
//     printf("1) %s\n", (void*)list->data);
//     printf("2) %s\n", (void*)list->next->data);
//     printf("3) %p\n\n", (void*)list->next->next);
//     mx_pop_back(&list);
//     printf("1) %s\n", (void*)list->data);
//     printf("2) %p\n\n", (void*)list->next);
//     mx_pop_back(&list);
//     printf("1) %p\n\n", (void*)list);
//     mx_pop_back(&list);
//     printf("1) %p\n\n", (void*)list);
//     mx_pop_back(&list);
//     printf("1) %p\n\n", (void*)list);
//     mx_pop_back(&list);
//     printf("1) %p\n\n", (void*)list);
//     mx_pop_back(&list); 
//     printf("1) %p\n\n", (void*)list);
    
//     return 0;
// }
