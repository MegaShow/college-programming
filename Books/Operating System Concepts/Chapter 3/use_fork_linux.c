#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    } else if (pid == 0) {
        // child process
        execlp("/bin/ls", "ls", NULL);
    } else {
        // parent will wait for the child to complete
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
}
