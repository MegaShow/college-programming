/*
ID: megaxiu1
LANG: C++
TASK: milk2
*/

#include <cstdio>
#include <algorithm>
using namespace std;

int cnt[5001][2];
int *arr[5001];

bool cmp(int* a, int* b){
    return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
}

int main(){
    freopen("milk2.in", "r", stdin);
    freopen("milk2.out", "w", stdout);
    int n, max = 0, nmax = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d%d", &cnt[i][0], &cnt[i][1]);
        arr[i] = cnt[i];
    }
    sort(arr, arr + n, cmp);
    for(int i = 1; i < n; i++){
        if(arr[i][0] <= arr[i-1][1] && arr[i][1] >= arr[i-1][1]){
            arr[i][0] = arr[i-1][0];
            arr[i-1][1] = arr[i][1];
        }
        else if(arr[i][0] >= arr[i-1][0] && arr[i][1] <= arr[i-1][1]){
            arr[i][0] = arr[i-1][0];
            arr[i][1] = arr[i-1][1];
        }
    }
    //for(int i = 0; i < n; i++){
    //    printf("%d %d\n", arr[i][0], arr[i][1]);
    //}
    max = arr[0][1] - arr[0][0];
    for(int i = 1; i < n; i++){
        if(max < arr[i][1] - arr[i][0])
            max = arr[i][1] - arr[i][0];
        if(nmax < arr[i][0] - arr[i-1][1])
            nmax = arr[i][0] - arr[i-1][1];
    }
    printf("%d %d\n", max, nmax);
}
