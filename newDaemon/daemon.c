#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid;
    struct rlimit flim;

    if ((pid = fork()) < 0)
        return -1;
    if (pid != 0) {
        printf("Daemon started with PID =%d\n", pid);
        exit(0);
    }
    setsid();
    chdir("/");
    
    getrlimit(RLIMIT_NOFILE, &flim);
    for (rlim_t i = 0; i < flim.rlim_max; i++)
        close(i);
    for (;;)
    pause();

    return 0;
}
