#include "log_utils.h"

char* mx_get_formatted_date() {
    time_t rawtime;
    struct tm * timeinfo;
    char *str = mx_strnew(25);
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    mx_strcat(str, "[");
    mx_strcat(str, mx_itoa(timeinfo->tm_mday));
    mx_strcat(str, ".");
    mx_strcat(str, mx_itoa(timeinfo->tm_mon + 1));
    mx_strcat(str, ".");
    mx_strcat(str, mx_itoa(timeinfo->tm_year + 1900));
    mx_strcat(str, " | ");
    mx_strcat(str, mx_itoa(timeinfo->tm_hour));
    mx_strcat(str, ":");
    mx_strcat(str, mx_itoa(timeinfo->tm_min));
    mx_strcat(str, ":");
    mx_strcat(str, mx_itoa(timeinfo->tm_sec));
    mx_strcat(str, "]");

    return str;
}

char* mx_get_formatted_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char *str = mx_strnew(25);
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
   
    mx_strcat(str, mx_itoa(timeinfo->tm_hour));
    mx_strcat(str, ":");
    mx_strcat(str, mx_itoa(timeinfo->tm_min));
    // mx_strcat(str, ":");
    // mx_strcat(str, mx_itoa(timeinfo->tm_sec));

    return str;
}

void mx_log_SSL_errors(char* file) {
    FILE *fd;

    if ((fd = fopen(file, "a+")) == NULL) 
        return;
    ERR_print_errors_fp(fd);

    fclose(fd);
}

void mx_log_msg(char* file, char* str) {
    FILE *fd;
    char *time;

    if ((fd = fopen(file, "a+")) == NULL) 
        return;
    time = mx_get_formatted_date();

    fprintf(fd, "%s %s\n", time, str);

    fclose(fd);
    mx_strdel(&time);
}

void mx_log_err(char* file, char* str) {
    char *new_str = mx_strjoin("ERROR: ", str);

    mx_log_msg(file, new_str);
    mx_strdel(&new_str);
}

void mx_log_info(char* file, char* str) {
    char *new_str = mx_strjoin("INFO: ", str);

    mx_log_msg(file, new_str);
    mx_strdel(&new_str);
}
