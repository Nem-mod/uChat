#include "../inc/libmx.h"

t_list *mx_create_node(void *data) {
    t_list *list = malloc(sizeof(*list));
    
    list->data = data;
    list->next = NULL;
    return list;
}

/*int main() {
    char str[] = "Hello world!";
    t_list *a = mx_create_node(str);
    printf("%s\n", a->data);
    
    return 0;
}*/
