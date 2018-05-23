#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "buffer.h"

typedef struct {
    int sleepTime;
    int keepTime;
    bufferItem productId;
} Parameter;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void InputAndCreateThread(pthread_t tid[], int n);
void* Producer(void* param);
void* Consumer(void* param);

int main(int argv, char* args[]) {
    if (argv != 4) {
        fprintf(stderr, "the number of parameters is invalid\n");
        return -1;
    }
    int time = atoi(args[1]);
    int numOfP = atoi(args[2]);
    int numOfC = atoi(args[3]);
    if (time == 0 || numOfP == 0 || numOfC == 0) {
        fprintf(stderr, "invalid parameters");
        return -1;
    }
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_t tid[numOfP + numOfC];
    InputAndCreateThread(tid, numOfP + numOfC);
    sleep(time);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}

void InputAndCreateThread(pthread_t tid[], int n) {
    int threadId;
    char type;
    for (int i = 0; i < n; i++) {
        scanf("%d%c", &threadId, &type);
        scanf("%c", &type);
        Parameter* p = malloc(sizeof(Parameter));
        if (type == 'P') {
            scanf("%d%d%d", &p->sleepTime, &p->keepTime, &p->productId);
            pthread_create(&tid[i], NULL, Producer, p);
        } else if (type == 'C') {
            scanf("%d%d", &p->sleepTime, &p->keepTime);
            pthread_create(&tid[i], NULL, Consumer, p);
        } else {
            fprintf(stderr, "invalid input\n");
            exit(-1);
        }
    }
}

void* Producer(void* param) {
    Parameter* p = (Parameter*) param;
    int sleepTime = p->sleepTime;
    int keepTime = p->keepTime;
    bufferItem productId = p->productId;
    free(p);
    while (true) {
        sleep(sleepTime);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if (insertItem(productId)) {
            fprintf(stderr, "report error condition\n");
            exit(-1);
        } else {
            printf("producer produced %d\n", productId);
            sem_post(&full);
        }
        sleep(keepTime);
        pthread_mutex_unlock(&mutex);
    }
}

void* Consumer(void* param) {
    Parameter* p = (Parameter*) param;
    int sleepTime = p->sleepTime;
    int keepTime = p->keepTime;
    free(p);
    bufferItem randItem;
    while (true) {
        sleep(sleepTime);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if (removeItem(&randItem)) {
            fprintf(stderr, "report error condition\n");
            exit(-1);
        } else {
            printf("consumer consumed %d\n", randItem);
            sem_post(&empty);
        }
        sleep(keepTime);
        pthread_mutex_unlock(&mutex);
    }
}
