#include "client.h"

t_file* mx_create_file(char* path, int size) {
    t_file *file = malloc(sizeof(t_file));

    file->path = path;
    file->size = size; // TODO: create func to get file size

    return file;
}
