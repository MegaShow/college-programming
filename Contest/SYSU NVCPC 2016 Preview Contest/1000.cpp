#include <cstdio>
#include <algorithm>
using namespace std;

int arr[26];

int main(){
    int n;
    int sum = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    sort(arr, arr + n);
    arr[n-1] = 2;
    for(int i = 0; i < 26; i++){
        sum += arr[i];
    }
    printf("%d\n", sum);
    return 0;
}
