/* 4186 Matrix Addition */

#include <cstdio>

void InputMatrix(int n, int* arr){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", arr+n*i+j);
        }
    }
}

void AddMatrix(int n, int* a, int* b){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            *(a+n*i+j) += *(b+n*i+j);
        }
    }
}

void PrintMatrix(int n, int* arr){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++)
            printf("%d ", *(arr+n*i+j));
        printf("%d\n", *(arr+n*i+n-1));
    }
}

int main(){
    int n;
    scanf("%d", &n);
    while(n){
        int a[n][n], b[n][n];
        InputMatrix(n, (int*)a);
        InputMatrix(n, (int*)b);
        AddMatrix(n, (int*)a, (int*)b);
        PrintMatrix(n, (int*)a);
        scanf("%d", &n);
    }
    return 0;
}
