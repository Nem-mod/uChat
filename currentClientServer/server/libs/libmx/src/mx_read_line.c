#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *static_buf;
    char *temp;
    char *buf;
    int delim_index;
    size_t read_count;

    if (read(fd, NULL, 0) < 0 || fd == -1)
		return -2;

    if (*lineptr != NULL)
        mx_strdel(lineptr);

    if (static_buf != NULL) {
        delim_index = mx_get_char_index(static_buf, delim);
        if (delim_index == -1) {
            *lineptr = mx_strdup(static_buf);
            mx_strdel(&static_buf);
        }
        else {
            *lineptr = mx_strndup(static_buf, delim_index);

            temp = static_buf;
            static_buf = mx_strdup(&static_buf[delim_index + 1]);
            mx_strdel(&temp);
            
            return mx_strlen(*lineptr);
        }
    }

    buf = mx_strnew(buf_size);
    while((read_count = read(fd, buf, buf_size)) > 0) {
        if (read_count < buf_size) {
            temp = buf;
            buf = mx_strndup(buf, read_count);
            mx_strdel(&temp);
        }
        delim_index = mx_get_char_index(buf, delim);
        if (delim_index == -1) {
            temp = *lineptr;
            *lineptr = mx_strjoin(*lineptr, buf);
            mx_strdel(&temp);
            if (read_count < buf_size) {
                mx_strdel(&buf);
                return -1;
            }
        }
        else {
            temp = static_buf;
            static_buf = mx_strdup(&buf[delim_index + 1]);
            mx_strdel(&temp);

            temp = buf;
            buf = mx_strndup(buf, delim_index);
            mx_strdel(&temp);

            temp = *lineptr;
            *lineptr = mx_strjoin(*lineptr, buf);
            mx_strdel(&temp);

            break;
        }
    }
    mx_strdel(&buf);

    if (read_count == 0 && delim_index == -1)
        return -1;
    return mx_strlen(*lineptr);
}

// int main() {
//     char *str = NULL;
//     int r_file = open("../tests/own", O_RDONLY);
    
//     printf("res: %d\n%s\n________\n", mx_read_line(&str, 7, '\n', r_file), str);
//     // printf("res: %d\n%s\n________\n", mx_read_line(&str, 35, 'I', r_file), str);
//     // printf("res: %d\n%s\n________\n", mx_read_line(&str, 7, '3', r_file), str);
//     // printf("res: %d\n%s\n________\n", mx_read_line(&str, 7, '\n', r_file), str);
//     // printf("res: %d\n%s\n________\n", mx_read_line(&str, 7, '\0', r_file), str);

//     mx_strdel(&str);
//     close(r_file);

//     return 0;
// }
