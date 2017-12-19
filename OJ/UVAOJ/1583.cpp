// UVA1583 MegaShow 2017.2.3

#include <cstdio>

int arr[100099];

int main(){
    int n, sum;
    for(int i = 1; i < 100000; i++){
        sum = i;
        for(int k = i; k; k /= 10)
            sum += k % 10;
        if(arr[sum] == 0)
            arr[sum] = i;
    }
    scanf("%d", &n);
    while(n--){
        scanf("%d", &sum);
        printf("%d\n", arr[sum]);
    }
}
