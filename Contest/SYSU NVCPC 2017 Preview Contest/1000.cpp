#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        int *arr = new int[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        sort(arr, arr+n, cmp);
        int count = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            if (sum >= m)   break;
            sum += arr[i];
            count++;
        }
        printf("%d\n", count);
        delete []arr;
    }
}
