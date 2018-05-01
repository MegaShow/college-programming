#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

DWORD sum;
DWORD WINAPI Summation(LPVOID param);

int main(int argv, char* args[]) {
    DWORD threadId;
    HANDLE threadHandle;
    int param;
    if (argv != 2) {
        fprintf(stderr, "usage: ./a.exe <integer value>\n");
        return -1;
    }
    param = atoi(args[1]);
    if (param < 0) {
        fprintf(stderr, "%d must be >= 0\n", atoi(args[1]));
        return -1;
    }
    threadHandle = CreateThread(NULL, 0, Summation, &param, 0, &threadId);
    if (threadHandle != NULL) {
        WaitForSingleObject(threadHandle, INFINITE);
        CloseHandle(threadHandle);
        printf("sum = %d\n", sum);
    }
}

DWORD WINAPI Summation(LPVOID param) {
    DWORD upper = *(DWORD*) param;
    for (DWORD i = 1; i <= upper; i++) {
        sum += i;
    }
    return 0;
}
