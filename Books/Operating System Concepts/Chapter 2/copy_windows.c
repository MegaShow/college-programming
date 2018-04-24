#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argv, char** args) {
    if (argv < 3) {
        printf("Lack of parameter.\n");
        return -1;
    }
    /*
    HANDLE WINAPI CreateFile(
        _In_     LPCTSTR               lpFileName,
        _In_     DWORD                 dwDesiredAccess,
        _In_     DWORD                 dwShareMode,
        _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        _In_     DWORD                 dwCreationDisposition,
        _In_     DWORD                 dwFlagsAndAttributes,
        _In_opt_ HANDLE                hTemplateFile
    ); */
    HANDLE inFile = CreateFile(
        args[1],
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );
    if (inFile == INVALID_HANDLE_VALUE) {
        printf("Open file %s failed.\n", args[1]);
        return -1;
    }
    /*
    DWORD WINAPI GetFileSize(
        _In_      HANDLE  hFile,
        _Out_opt_ LPDWORD lpFileSizeHigh
    ); */
    DWORD fileSize = GetFileSize(inFile, NULL);
    char* buffer = (char*) malloc(fileSize);
    /*
    BOOL WINAPI ReadFile(
        _In_        HANDLE       hFile,
        _Out_       LPVOID       lpBuffer,
        _In_        DWORD        nNumberOfBytesToRead,
        _Out_opt_   LPDWORD      lpNumberOfBytesRead,
        _Inout_opt_ LPOVERLAPPED lpOverlapped
    ); */
    if(ReadFile(inFile, buffer, fileSize, NULL, NULL) != TRUE) {
        printf("Read file %s failed.\n", args[1]);
        CloseHandle(inFile);
        free(buffer);
        return -1;
    }
    /*
    BOOL WINAPI CloseHandle(
        _In_ HANDLE hObject
    ); */
    CloseHandle(inFile);
    HANDLE outFile = CreateFile(
        args[2],
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );
    if (outFile == INVALID_HANDLE_VALUE) {
        printf("Create file %s failed.\n", args[2]);
        free(buffer);
        return -1;
    }
    /*
    BOOL WINAPI WriteFile(
        _In_        HANDLE       hFile,
        _In_        LPCVOID      lpBuffer,
        _In_        DWORD        nNumberOfBytesToWrite,
        _Out_opt_   LPDWORD      lpNumberOfBytesWritten,
        _Inout_opt_ LPOVERLAPPED lpOverlapped
    ); */
    if (WriteFile(outFile, buffer, fileSize, NULL, NULL) != TRUE) {
        printf("Write file %s failed.\n", args[2]);
        CloseHandle(outFile);
        free(buffer);
        return -1;
    }
    CloseHandle(outFile);
    free(buffer);
}
