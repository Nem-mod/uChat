#include "../inc/libmx.h"

char *mx_file_to_str(const char *filename) {
    int len = mx_file_len(filename);
    int r_file = open(filename, O_RDONLY);

    if (len <= 0 || r_file == -1)
        return NULL;

    char *str = mx_strnew(len);

    read(r_file, str, len);
    close(r_file);

    return str;
}

// int main() {
//     char *str = mx_file_to_str("../../inc/t.txt");

//     printf("%s", str);

//     return 0;
// }
