#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int value = 5;

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        value += 15;
    } else if (pid > 0) {
        wait(NULL);
        printf("Parent: value = %d\n", value);
        exit(0);
    }
}
