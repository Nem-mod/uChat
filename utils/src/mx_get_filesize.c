#include <sys/stat.h>
#include <fcntl.h> 

unsigned long get_file_size(char *filename) {
    unsigned int size = 0;
    struct stat st;
    if (stat(filename, &st) == 0) {
        size = (unsigned int)st.st_size;
    } 
    // else {
    //     printf("Error: Unable to get file size\n");
    // }
    return size;
}
