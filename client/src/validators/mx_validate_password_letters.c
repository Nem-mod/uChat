#include "client.h"

int mx_validate_password_letters(const char *password) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "[a-zA-Z]", 0);
    if (ret != 0) {
        return 1;
    }

    ret = regexec(&regex, password, 0, NULL, 0);

    return ret;
}
