#include "../inc/libmx.h"

int mx_file_len(const char *filename) {
    int r_file = open(filename, O_RDONLY);
    int len = 0;
    char buf;

    if (r_file == -1)
        return -1;

    int is_read = read(r_file, &buf, 1);

    while (is_read > 0) {
        is_read = read(r_file, &buf, 1);
        len++;
    }
    close(r_file);

    return len;
}
