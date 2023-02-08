#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    char hex_chars[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    if (nbr < 1 || nbr > 9223372036854775807) {
        char *zero = malloc(sizeof(char));
        zero[0] = hex_chars[0];
        
        return zero;
    }
    
    char *hex = malloc(17 * sizeof(char));
    int len = 0;
    
    if (hex == NULL)
        return NULL;
    while (nbr > 0) {
        hex[len] = hex_chars[nbr % 16];
        nbr /= 16;
        len++;
    }
    for (int i = 0; i < len / 2; i++) {
        char temp = hex[i];
        hex[i] = hex[len - i - 1];
        hex[len - i - 1] = temp;
    }
    for (int i = len; i < 17; i++)
        hex[i] = '\0';
    
    return hex;
}

// int main() {
//     mx_printstr(mx_nbr_to_hex(175));

//     return 0;
// }
