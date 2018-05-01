#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int** a;
int** b;
int** c;
void* runner(void* param);

typedef struct {
    int row;
    int col;
    int k;
} Position;

int main() {
    int m, k, n;
    printf("Input m k n\n");
    scanf("%d%d%d", &m, &k, &n);
    a = malloc(sizeof(int*) * m);
    b = malloc(sizeof(int*) * k);
    c = malloc(sizeof(int*) * m);
    for (int i = 0; i < m || i < k; i++) {
        if (i < m) {
            a[i] = malloc(sizeof(int) * k);
            c[i] = malloc(sizeof(int) * n);
        }
        if (i < k) {
            b[i] = malloc(sizeof(int) * n);
        }
    }
    printf("Input matrix A(m * k)\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    printf("Input matrix B(k * n)\n");
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &b[i][j]);
        }
    }
    pthread_t arr[m][n];
    pthread_attr_t attr[m][n];
    Position pos[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            pos[i][j].k = k;
            pos[i][j].row = i;
            pos[i][j].col = j;
            pthread_attr_init(&attr[i][j]);
            pthread_create(&arr[i][j], &attr[i][j], runner, &pos[i][j]);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            pthread_join(arr[i][j], NULL);
        }
    }
    printf("Output matrix C(m * n)\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", c[i][j]);
        }
        printf("%d\n", c[i][n - 1]);
    }
    for (int i = 0; i < m || i < k; i++) {
        if (i < m) {
            free(a[i]);
            free(c[i]);
        }
        if (i < k) {
            free(b[i]);
        }
    }
    free(a);
    free(b);
    free(c);
}

void* runner(void* param) {
    Position pos = *(Position*) param;
    c[pos.row][pos.col] = 0;
    for (int i = 0; i < pos.k; i++) {
        c[pos.row][pos.col] += a[pos.row][i] * b[i][pos.col];
    }
    pthread_exit(0);
}

