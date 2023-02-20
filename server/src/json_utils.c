#include "../inc/server.h"

/* Simple function to get the message string from parsed json object */
char *message_get_message(json_object *message) {
    const char *msg = json_object_to_json_string(
        json_object_object_get(message, "Message")
    );

    char *res = mx_strdup(msg);
    free((char*) msg);
    return res;
}

