#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("b\n");
    } else {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("c\n");
        } else {
            printf("a\n");
        }
    }
}
