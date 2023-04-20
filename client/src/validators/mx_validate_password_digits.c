#include "client.h"

int mx_validate_password_digits(const char *password) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[0-9]", 0);
    if (ret != 0) {
        return 1;
    }

    ret = regexec(&regex, password, 0, NULL, 0);

    return ret;
}
