#include "../inc/client.h"

/* Get message string from json message object */
const char *message_get_message(json_object *message) {
  return (
    json_object_get_string(json_object_object_get(message, "Message"))
  );
}

const char *message_get_datetime(json_object *message) {
  return (
    json_object_get_string(json_object_object_get(message, "Date and time"))
  );
}

// const char *time_to_string(struct tm *tm) {
//     // char *date = mx_strnew(9);
//     // char *temp = mx_itoa(tm.tm_mday);
//     // if (mx_strlen(temp) == 1) {
//     //     date[0] = '0';
//     //     date[1] = temp[0];
//     // }
//     // else {
//     //     date[0] = temp[0];
//     //     date[1] = temp[1];
//     // }
//     // date[2] = '/';
//     // temp = mx_itoa(tm.tm_mon);
//     // if (mx_strlen(temp) == 1) {
//     //     date[3] = '0';
//     //     date[4] = temp[0];
//     // }
//     // else {
//     //     date[3] = temp[0];
//     //     date[4] = temp[1];
//     // }
//     return NULL;
// }
