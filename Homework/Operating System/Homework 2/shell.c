#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define MAX_COMMAND 10

struct __queue {
    char data[MAX_COMMAND][MAX_LINE + 1];
    int front;
    int rear;
    int size;
};

typedef struct __queue Queue;
typedef Queue* QueuePointer;

Queue history;
bool isSIGINT;
int cmdNum;

void Push(QueuePointer qp, char data[]);
void Pop(QueuePointer qp);
void Setup(char inputBuffer[], int* argvPointer, char* args[], bool* isBackgroundPointer);
void ShowHistory();

int main() {
    struct sigaction handle;
    memset(&handle, 0, sizeof(struct sigaction));
    handle.sa_handler = ShowHistory;
    sigaction(SIGINT, &handle, NULL);
    history.front = history.rear = history.size = 0;
    char inputBuffer[MAX_LINE + 1];
    bool isBackground;
    int argv;
    char* args[MAX_LINE / 2 + 1];
    while (1) {
        Setup(inputBuffer, &argv, args, &isBackground);
        if (argv > 0) {
            pid_t pid = fork();
            if (pid == 0) {
                int result = execvp(args[0], args);
                if (result == -1) {
                    perror(args[0]);
                }
                exit(0);
            } else {
                if (isBackground == false) {
                    waitpid(pid, NULL, 0);
                } else {
                    printf("[Background] %s\n", args[0]);
                }
            }
        }
    }
}

void Push(QueuePointer qp, char data[]) {
    sprintf(qp->data[qp->rear++], "%s", data);
    if (qp->rear == MAX_COMMAND) {
        qp->rear = 0;
    }
    if (qp->size != MAX_COMMAND) {
        qp->size++;
    } else {
        cmdNum++;
        qp->front++;
        if (qp->front == MAX_COMMAND) {
            qp->front = 0;
        }
    }
}

void Pop(QueuePointer qp) {
    if (qp->size != 0) {
        qp->size--;
        qp->front++;
        if (qp->front == MAX_COMMAND) {
            qp->front = 0;
        }
    } else {
        puts("error: queue has no entry");
    }
}

void Setup(char inputBuffer[], int* argvPointer, char* args[], bool* isBackgroundPointer) {
    if (isSIGINT) {
        isSIGINT = false;
    } else {
        printf("\033[1;32msh\033[m> ");
    }
    fflush(stdin);
    *argvPointer = 0;
    *isBackgroundPointer = false;
    char* result = fgets(inputBuffer, MAX_LINE + 1, stdin);
    if (result == NULL) {
        if (isSIGINT) {
            return;
        }
        puts("exit\nexit");
        exit(1);
    } else if (inputBuffer[0] == 0 || inputBuffer[0] == '\n') {
        return;
    }
    int len = strlen(inputBuffer);
    if (inputBuffer[0] == 'r' && (inputBuffer[1] == '\n' || inputBuffer[1] == ' ')) {
        if (history.size == 0) {
            puts("no history");
            return;
        }
        int index = history.rear != 0 ? history.rear - 1 : MAX_COMMAND - 1;
        if (inputBuffer[1] == '\n') {
            sprintf(inputBuffer, "%s", history.data[index]);
        } else {
            bool flag = false;
            for (int i = 0; i < history.size; i++) {
                if (history.data[index][0] == inputBuffer[2]) {
                    sprintf(inputBuffer, "%s", history.data[index]);
                    flag = true;
                    break;
                }
                index--;
                if (index == -1) {
                    index = MAX_COMMAND - 1;
                }
            }
            if (flag == false) {
                printf("history %c not found\n", inputBuffer[2]);
                return;
            }
        }
    }
    Push(&history, inputBuffer);
    if (inputBuffer[len - 2] == '&') {
        *isBackgroundPointer = true;
        inputBuffer[len - 2] = 0;
    }
    args[*argvPointer] = strtok(inputBuffer, " \t\n");
    if (args[*argvPointer] != NULL) {
        (*argvPointer)++;
    }
    while ((args[*argvPointer] = strtok(NULL, " \t\n")) != NULL) {
        (*argvPointer)++;
    }
    if (strcmp(args[0], "exit") == 0) {
        puts("exit");
        exit(1);
    }
    args[*argvPointer] = NULL;
}

void ShowHistory() {
    isSIGINT = true;
    char str[15];
    write(STDOUT_FILENO, "\n", 1);
    for (int i = 0, j = history.front; i < history.size; i++) {
        sprintf(str, "command %d: ", i + 1 + cmdNum);
        write(STDOUT_FILENO, str, strlen(str));
        write(STDOUT_FILENO, history.data[j], strlen(history.data[j]));
        j++;
        if (j == MAX_COMMAND) {
            j = 0;
        }
    }
    write(STDOUT_FILENO, "\033[1;32msh\033[m> ", 14);
}
