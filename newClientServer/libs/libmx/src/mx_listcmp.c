#include "../inc/libmx.h"

int mx_listcmp(t_list *l1, t_list *l2) {
    if (mx_list_size(l1) != mx_list_size(l2))
        return -1;
    while (l1 != NULL && l2 != NULL) {
        if (l1->data != l2->data) {
            return -1;
        }
        l1 = l1->next;
        l2 = l2->next;
    }
    return 0;
}

// int main() {
//     char s1[] = "Hello";
//     char s2[] = "World";
//     char s3[] = "Lorem";

//     t_list *l1 = mx_create_node(s1);
//     mx_push_back(&l1, s2);

//     t_list *l2 = mx_create_node(s1);
//     mx_push_back(&l2, s2);

//     t_list *l3 = mx_create_node(s1);
//     mx_push_back(&l3, s3);
//     mx_push_back(&l3, s2);

//     printf("%d\n", mx_listcmp(l1, l2));
//     printf("%d\n", mx_listcmp(l2, l3));

//     return 0;
// }
