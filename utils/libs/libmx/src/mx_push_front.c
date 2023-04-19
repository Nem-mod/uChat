#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
    if (list == NULL)
        return;
    if (*list == NULL) {
        *list = mx_create_node(data);
        return;
    }
    t_list *node = mx_create_node(data);

    node->next = *list;
    *list = node;
}
