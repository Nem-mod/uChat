#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
    if (list == NULL)
        return 0;
    t_list *temp = list;
    int len;
    for (len = 1; temp->next != NULL; len++)
        temp = temp->next;

    return len;
}

// int main() {
//     t_list *list = malloc(sizeof(*list));
//     list->data = "Hello";
//     list->next = malloc(sizeof(list->next));
//     list->next->data = "World";
//     list->next->next = malloc(sizeof(list->next->next));
//     list->next->next->data = "lorem Ipsum";
//     list->next->next->next = NULL;
//     
//     printf("%s\n", (void*)list->data);
//     printf("%s\n", (void*)list->next->data);
//     printf("%s\n", (void*)list->next->next->data);
//     printf("%d\n", mx_list_size(list));
//     
//     
//     return 0;
// } 
