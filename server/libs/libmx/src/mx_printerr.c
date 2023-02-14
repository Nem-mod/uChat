#include "../inc/libmx.h"

void mx_printerr(const char *s) {
    if (s == NULL)
        return;
    for (int i = 0; s[i] != '\0'; i++)
        write(2, &s[i], 1);
}
