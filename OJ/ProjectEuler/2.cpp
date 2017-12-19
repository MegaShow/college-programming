// Euler 002

#include <cstdio>

int main(){
    int n;
    n = 4e6; // scanf("%d", &n);
    int sum = 0;
    int arr[45] = {1,2};
    for(int i = 2; i < 45; i++){
        arr[i] = arr[i-1] + arr[i-2];
        if(arr[i] >= n){
            arr[i+1] = 0;
            break;
        }
    }
    for(int i = 1; arr[i]; i++){
        if(arr[i] & 1)
            continue;
        sum += arr[i];
    }
    printf("%d\n", sum);
}
