#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SEQUENCE 10

struct __sharedData {
    long fibSequence[MAX_SEQUENCE];
    int sequenceSize;
};

typedef struct __sharedData SharedData;
typedef SharedData* SharedDataPointer;

int main(int argv, char** args) {
    if (argv <= 1) {
        printf("no input parameter\n");
        return 1;
    } else if (argv >= 3) {
        printf("too much parameters\n");
        return 1;
    }
    int var = atoi(args[1]);
    if (var == 0 || var >= MAX_SEQUENCE) {
        printf("invalid parameters\n");
        return 1;
    }
    int shmid = shmget(0, sizeof(SharedData), 0);
    if (shmid == -1) {
        perror("create shared memory failed\nerror code");
        return 1;
    }
    SharedDataPointer data = (SharedDataPointer) shmat(shmid, 0, 0);
    if ((long)data == -1) {
        perror("get shared memory address failed\nerror code");
        return 1;
    }
    data->sequenceSize = var;
    pid_t pid = fork();
    if (pid == 0) {
        data->fibSequence[0] = 1;
        data->fibSequence[1] = 1;
        for (int i = 2; i < data->sequenceSize; i++) {
            data->fibSequence[i] = data->fibSequence[i - 1] + data->fibSequence[i - 2];
        }
    } else {
        wait(0);
        printf("%ld", data->fibSequence[0]);
        for (int i = 1; i < data->sequenceSize; i++) {
            printf(" %ld", data->fibSequence[i]);
        }
        printf("\n");
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("delete shared memory failed\nerror code");
            return 1;
        }
    }
    return 0;
}
