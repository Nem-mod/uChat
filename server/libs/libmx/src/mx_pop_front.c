#include "../inc/libmx.h"

void mx_pop_front(t_list **list) {
    if (list == NULL || *list == NULL)
        return;
    t_list *temp = *list;
    
    *list = temp->next;
    free(temp);
    temp = NULL;
}

// int main() {
//     // t_list *list = malloc(sizeof(*list));
//     // list->data = "Hello";
//     // list->next = malloc(sizeof(list->next));
//     // list->next->next = NULL;
//     // list->next->data = "World";

//     char *str1 = "Hello";
//     char *str2 = "World";
//     t_list *list = mx_create_node(str1);
//     list->next = mx_create_node(str2);
    
//     // printf("%s\n", (void*)list->data);
//     // printf("%s\n", (void*)list->next->data);
//     // mx_pop_front(&list);
//     // printf("%s\n", (void*)list->data);
//     // printf("%s\n", (void*)list->next->data);
//     printf("%p\n", (void*)list);
//     printf("%p\n\n", (void*)list->next);
//     mx_pop_front(&list);
//     printf("%p\n", (void*)list);
//     printf("%p\n\n", (void*)list->next);
//     mx_pop_front(&list);
//     printf("%p\n", (void*)list);
//     printf("%p\n", (void*)list->next);
    
    
//     return 0;
// }
