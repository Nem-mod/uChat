#include "../inc/libmx.h"

bool mx_isspace(int c) {
    if (c == 32 || c == '\t' || c == '\n' ||
        c == '\v' ||c == '\f' || c == '\r')
        return true;
    return false;
}
