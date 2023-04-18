#include "client.h"

t_contact* mx_create_contact(char* name, char* icon_path, int size) {
    t_contact *contact = malloc(sizeof(t_contact));

    contact->name = name;
    contact->icon = mx_create_file(icon_path, size);

    return contact;
}
