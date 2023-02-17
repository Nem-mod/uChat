#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long res = 0;
    int len;
    
    if (hex == NULL)
        return 0;
    for (len = 0; hex[len] != '\0'; len++);
    len--;
    for (int i = 0; hex[i] != '\0'; i++) {
        if (!mx_isdigit(hex[i]) && !mx_isalpha(hex[i]))
            return 0;
        if (mx_isdigit(hex[i]))
            res += (hex[i] - '0') * mx_pow(16, len - i);
        if (mx_isalpha(hex[i])) {
            if (mx_islower(hex[i]))
                res += (hex[i] - 'a' + 10) * mx_pow(16, len - i);
            else
                res += (hex[i] - 'A' + 10) * mx_pow(16, len - i);
        }
    }
    return res;
}

// int main() {
//     printf("%lu", mx_hex_to_nbr("FADE"));

//     return 0;
// }
