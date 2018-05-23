#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>
#include <unistd.h>

long startTime;
int readCount;
pthread_mutex_t readCountMutex;
pthread_mutex_t writeMutex;

typedef struct {
    int threadId;
    int sleepTime;
    int keepTime;
} Parameter;

void InputAndCreateThread(pthread_t tid[], int n);
void* Writer(void* param);
void* Reader(void* param);

int main(int agrv, char* args[]) {
    if (agrv != 2) {
        fprintf(stderr, "invalid parameter\n");
        return -1;
    }
    int n = atoi(args[1]);
    if (n == 0) {
        fprintf(stderr, "invalid parameter\n");
        return -1;
    }
    readCount = 0;
    pthread_mutex_init(&readCountMutex, NULL);
    pthread_mutex_init(&writeMutex, NULL);
    pthread_t tid[n];
    startTime = time(NULL);
    InputAndCreateThread(tid, n);
    for (int i = 0; i < n; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&readCountMutex);
    pthread_mutex_destroy(&writeMutex);
}

void InputAndCreateThread(pthread_t tid[], int n) {
    char type;
    for (int i = 0; i < n; i++) {
        Parameter* p = malloc(sizeof(Parameter));
        scanf("%d%c", &p->threadId, &type);
        scanf("%c%d%d", &type, &p->sleepTime, &p->keepTime);
        if (type == 'R') {
            pthread_create(&tid[i], NULL, Reader, p);
        } else if (type == 'W') {
            pthread_create(&tid[i], NULL, Writer, p);
        } else {
            fprintf(stderr, "invalid input\n");
            exit(-1);
        }
    }
}

void* Writer(void* param) {
    Parameter* p = (Parameter*) param;
    sleep(p->sleepTime);
    printf("%ld: Thread %d wants to write\n", time(NULL) - startTime, p->threadId);
    pthread_mutex_lock(&writeMutex);
    printf("%ld: Thread %d starts writing\n", time(NULL) - startTime, p->threadId);
    sleep(p->keepTime);
    printf("%ld: Thread %d finishes writing\n", time(NULL) - startTime, p->threadId);
    pthread_mutex_unlock(&writeMutex);
    free(p);
    pthread_exit(0);
}

void* Reader(void* param) {
    Parameter* p = (Parameter*) param;
    sleep(p->sleepTime);
    printf("%ld: Thread %d wants to read\n", time(NULL) - startTime, p->threadId);
    pthread_mutex_lock(&readCountMutex);
    readCount++;
    if (readCount == 1) {
        pthread_mutex_lock(&writeMutex);
    }
    pthread_mutex_unlock(&readCountMutex);
    printf("%ld: Thread %d starts reading\n", time(NULL) - startTime, p->threadId);
    sleep(p->keepTime);
    printf("%ld: Thread %d finishes reading\n", time(NULL) - startTime, p->threadId);
    pthread_mutex_lock(&readCountMutex);
    readCount--;
    if (readCount == 0) {
        pthread_mutex_unlock(&writeMutex);
    }
    pthread_mutex_unlock(&readCountMutex);
    free(p);
    pthread_exit(0);
}
