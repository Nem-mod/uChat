#include "client.h"

t_user* mx_json_create_user(const char* property) {
    return mx_create_user(mx_json_get_str(property, "login"),
                            mx_json_get_str(property, "password"),
                            mx_json_get_int(property, "user_id"),
                            NULL,
                            NULL,
                            0);
}
