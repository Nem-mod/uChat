#include "ssl_utils.h"


SSL_CTX* mx_init_context(bool is_server) {
    SSL_CTX *ctx;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    if (is_server)
        ctx = SSL_CTX_new(TLS_server_method());
    else
        ctx = SSL_CTX_new(TLS_client_method());

    if (ctx == NULL) {
        mx_log_err(SYSLOG, "Unable to create SSL context"); 
        mx_log_SSL_errors(SYSLOG);      
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void mx_use_certificate_key(SSL_CTX *ctx, char *certPath, char *keyPath) {
    if (SSL_CTX_use_certificate_file(ctx, certPath, SSL_FILETYPE_PEM) <= 0) {
        mx_log_err(SYSLOG, "Unable to get certificate");
        mx_log_SSL_errors(SYSLOG); 
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, keyPath, SSL_FILETYPE_PEM) <= 0)  {
        mx_log_err(SYSLOG, "Unable to get private key");   
        mx_log_SSL_errors(SYSLOG); 
        exit(EXIT_FAILURE);
    }
    if (!SSL_CTX_check_private_key(ctx)) {
        mx_log_err(SYSLOG, "Private key does not match the public certificate");  
        exit(EXIT_FAILURE);
    }
}

SSL* mx_init_SSL_session(SSL_CTX* ctx, int socket) {
    SSL* ssl;

    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        mx_log_err(SYSLOG, "Unable to create SSL structure");    
        mx_log_SSL_errors(SYSLOG);
        exit(EXIT_FAILURE);
    }
    if (SSL_set_fd(ssl, socket) == 0) {
        mx_log_err(SYSLOG, "Unable to link socket to SSL session");    
        mx_log_SSL_errors(SYSLOG);
        exit(EXIT_FAILURE);
    }

    return ssl;
}

void mx_SSL_log_print_error(SSL* ssl, int erno) {    
    if (erno != 1) {
        switch(SSL_get_error(ssl, erno)) {
            case SSL_ERROR_NONE:
                mx_log_err(SYSLOG, "error SSL_ERROR_NONE\n");
                break;
            case SSL_ERROR_SSL:
                mx_log_err(SYSLOG, "error SSL_ERROR_SSL\n");
                break;
            case SSL_ERROR_WANT_READ:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_READ\n");
                break;
            case SSL_ERROR_WANT_WRITE:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_WRITE\n");
                break;
            case SSL_ERROR_WANT_X509_LOOKUP:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_X509_LOOKUP\n");
                break;
            case SSL_ERROR_SYSCALL:
                mx_log_err(SYSLOG, "error SSL_ERROR_SYSCALL\n");
                break;
            case SSL_ERROR_ZERO_RETURN:
                mx_log_err(SYSLOG, "error SSL_ERROR_ZERO_RETURN \n");
                break;
            case SSL_ERROR_WANT_CONNECT:
                mx_log_err(SYSLOG, "error SSL_ERROR_WANT_CONNECT\n");
                break;
            default:
                mx_log_err(SYSLOG, "error unknown\n");
                break;
        }
        mx_log_SSL_errors(SYSLOG); 
    }
}

int mx_handshake(SSL* ssl, int is_server) {   
    int result;

    if (is_server)
        result = SSL_accept(ssl);
    else
        result = SSL_connect(ssl);

    if (result != 1) {
        mx_log_err(SYSLOG, "Handshake error");    
        mx_SSL_log_print_error(ssl, result);

        return 0;
    }
    return 1;
}

int mx_SSL_write(SSL* ssl, char* buffer) {
    int result;

    result = SSL_write(ssl, buffer, mx_strlen(buffer) + 1);
    if (result <= 0) {
        mx_log_err(SYSLOG, "Unable to write msg");   
        mx_SSL_log_print_error(ssl, result);
        return -1;
    }

    return result;
}

int mx_SSL_read(SSL* ssl, char* buffer) {
    int result;

    result = SSL_read(ssl, buffer, MAXBUFFER);
    if (result <= 0) {
        mx_log_err(SYSLOG, "Unable to read msg");   
        mx_SSL_log_print_error(ssl, result);
        return -1;
    }
    return result;
}

unsigned long  mx_SSL_sendfile(SSL* ssl, char* path, unsigned long  prepsize) {
    FILE* fd = fopen(path, "r");
    char buffer[MAXBUFFER];
    int len;
    if (fd == NULL) {
        fclose(fd);
        return -1;
    }

    unsigned long  as = 0;
    while ((len = fread(buffer, 1, MAXBUFFER, fd)) > 0 && as < prepsize) {
        int sent = SSL_write(ssl, buffer, len);
        as += sent;
        if (sent < 0) 
            mx_log_err("log_err.txt", "SSL_write() error");
    }
    mx_log_err("sent.txt", mx_itoa(as));
    fclose(fd);
    return len;
}

// static bool file_exists (char *filename) {
//   struct stat   buffer;   
//   return (stat (filename, &buffer) == 0);
// }

unsigned long mx_SSL_readfile(SSL* ssl, char* path, unsigned long size) {
    // if(file_exists(path)) {
    //     mx_strjoin(path, "1");
    //     mx_log_err("rec.txt", "File ex");
    // }
    //mx_log_err("rec.txt", mx_itoa((int)size));

    FILE* fd = fopen(path, "w+");
    if (fd == NULL) {
        fclose(fd);
        return -1;
    }

    char buffer[MAXBUFFER];
    unsigned long bytes_received;
    unsigned long total_bytes_received = 0;
    total_bytes_received = 0 ;
    //mx_log_err("rec.txt", "Rec start");
    while (total_bytes_received < size) {
        mx_memset(&buffer, 0, sizeof(buffer));
        bytes_received = SSL_read(ssl, buffer, MAXBUFFER);
        
        //mx_log_err("rec.txt", mx_itoa(bytes_received));
        //mx_log_err("rec.txt", "\n");
        if ((int)fwrite(buffer, sizeof(char), bytes_received, fd) != (int)bytes_received) {
            fclose(fd);
            return -1;
        }
        total_bytes_received += bytes_received;
        // mx_log_err("rec.txt", mx_itoa(total_bytes_received));
        // mx_log_err("rec.txt", buffer);
        
        
    }

    //mx_log_err("rec.txt", "Rec end");
    fclose(fd);
    return total_bytes_received;
}



