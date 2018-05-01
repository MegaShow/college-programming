#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum;
void* runner(void* param);

int main(int argv, char* args[]) {
    pthread_t tid;
    pthread_attr_t attr;
    if (argv != 2) {
        fprintf(stderr, "usage: ./a.out <integer value>\n");
        return -1;
    }
    if (atoi(args[1]) < 0) {
        fprintf(stderr, "%d must be >= 0\n", atoi(args[1]));
        return -1;
    }
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, args[1]);
    pthread_join(tid, NULL);
    printf("sum = %d\n", sum);
}

void* runner(void* param) {
    int upper = atoi(param);
    sum = 0;
    for (int i = 1; i <= upper; i++) {
        sum += i;
    }
    pthread_exit(0);
}
