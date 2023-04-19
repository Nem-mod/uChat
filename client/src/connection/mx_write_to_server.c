#include "client.h"

void mx_write_to_server(SSL* ssl, char* buffer) {

    if(buffer != NULL && mx_strlen(buffer) < (int)(sizeof(char) * MAXBUFFER)){
        mx_log_info(SYSLOG, "vvv Pass JSON to the server vvv");
        mx_log_info(SYSLOG, buffer);

        mx_SSL_write(ssl, buffer);
        mx_strdel(&buffer);
    } else
        mx_log_err(SYSLOG, "Write failed");
 
}
