#include <cstdio>

int arr[46] = {0, 1, 2, 3};

void f(int n){
    for(int i = 4; i <= n; i++)
        arr[i] = arr[i-1] + arr[i-2];
}

int main(){
    int num;
    scanf("%d", &num);
    f(num);
    printf("%d\n", arr[num]);
    return 0;
}
