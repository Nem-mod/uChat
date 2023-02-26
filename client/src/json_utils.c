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

const char *time_to_string() {
  time_t rawtime; // = time(NULL);
  time(&rawtime);
  struct tm *tm = localtime(&rawtime);

  char *date = mx_strnew(21);
  char *temp = mx_itoa(tm->tm_mday);
  if (mx_strlen(temp) == 1) {
    mx_strcat(date, "0");
    mx_strcat(date, temp);
  }
  else {
    // date[0] = temp[0];
    // date[1] = temp[1];
    mx_strcat(date, temp);
  }
  date[2] = '.';
  free(temp);
  temp = mx_itoa(tm->tm_mon + 1);
  if (mx_strlen(temp) == 1) {
    date[3] = '0';
    date[4] = temp[0];
  }
  else {
    // date[3] = temp[0];
    // date[4] = temp[1];
    mx_strcat(date, temp);
  }
  mx_strcat(date, ".");
  free(temp);
  mx_strcat(date, mx_itoa(tm->tm_year + 1900));
  mx_strcat(date, " | ");

  temp = mx_itoa(tm->tm_hour);
  if (mx_strlen(temp) == 1) {
    mx_strcat(date, "0");
    mx_strcat(date, temp);
  }
  else {
    mx_strcat(date, temp);
  }
  mx_strcat(date, ":");
  free(temp);
  temp = mx_itoa(tm->tm_min);
  if (mx_strlen(temp) == 1) {
    mx_strcat(date, "0");
    mx_strcat(date, temp);
  }
  else {
    mx_strcat(date, temp);
  }
  mx_strcat(date, ":");
  free(temp);
  temp = mx_itoa(tm->tm_sec);
  if (mx_strlen(temp) == 1) {
    mx_strcat(date, "0");
    mx_strcat(date, temp);
  }
  else {
    mx_strcat(date, temp);
  }
  free(temp);
  char *res = mx_strnew(mx_strlen(date) + 2);
  mx_strcat(res, "[");
  mx_strcat(res, date);
  mx_strcat(res, "]");
  free(date);
  return res;
}
