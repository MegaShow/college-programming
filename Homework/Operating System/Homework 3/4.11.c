#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int fib[46];
void* runner(void* param);

int main(int argv, char* args[]) {
    pthread_t tid;
    pthread_attr_t attr;
    if (argv != 2) {
        fprintf(stderr, "usage: ./a.out <integer value>\n");
        return -1;
    }
    int upper = atoi(args[1]);
    if (upper < 1) {
        fprintf(stderr, "%d must be >= 1\n", upper);
        return -1;
    }
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, &upper);
    pthread_join(tid, NULL);
    printf("%d", fib[0]);
    for (int i = 1; i < upper; i++) {
        printf(" %d", fib[i]);
    }
    printf("\n");
}

void* runner(void* param) {
    int upper = *(int*)param;
    fib[0] = fib[1] = 1;
    for (int i = 2; i < upper; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    pthread_exit(0);
}
