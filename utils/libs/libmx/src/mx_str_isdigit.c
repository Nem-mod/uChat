#include "../inc/libmx.h"

bool mx_str_isdigit(char *str) {
    bool isNum = false;
    int digit_count = 0;

    if(str == NULL)
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((!mx_isdigit(str[i]) && str[i] != '-' && !mx_isspace(str[i])) || (mx_isspace(str[i]) && isNum))
            return false;
        if ((str[i] == '-' || mx_isdigit(str[i])) && !isNum)
            isNum = true;
        else if (str[i] == '-' && isNum)
            return false;
        if (mx_isdigit(str[i]))
            digit_count++;
    }
    if (digit_count == 0)
        return false;
    return true;
}

// int main() {
//     printf("%d\n", mx_str_isdigit("0"));
//     printf("%d\n", mx_str_isdigit("5"));
//     printf("%d\n", mx_str_isdigit("128942194"));
//     printf("%d\n", mx_str_isdigit("-12893"));
//     printf("%d\n", mx_str_isdigit("    1248421"));
//     printf("%d\n", mx_str_isdigit("   -12312"));
//     printf("%d\n", mx_str_isdigit("124f"));
//     printf("%d\n", mx_str_isdigit("f214123"));
//     printf("%d\n", mx_str_isdigit("   1321-3213"));
//     printf("%d\n", mx_str_isdigit("-"));
//     printf("%d\n", mx_str_isdigit("        -"));
//     printf("%d\n", mx_str_isdigit("--1"));


//     return 0;
// }
