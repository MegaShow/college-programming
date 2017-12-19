// 1001. 序列的交并差集
#include <cstdio>
#include <set>
using namespace std;

int main() {
  int m, n;
  while (~scanf("%d%d", &m, &n)) {
    set<int> am, bm;
    int arr[m], brr[n];
    for (int i = 0; i < m; i++) {
      scanf("%d", &arr[i]);
      am.insert(arr[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &brr[i]);
      bm.insert(brr[i]);
    }
    for (int i = 0; i < m; i++) {
      if (bm.count(arr[i])) {
        printf("%d ", arr[i]);
      }
    }
    putchar('\n');
    for (int i = 0; i < m; i++) {
      printf("%d ", arr[i]);
    }
    for (int i = 0; i < n; i++) {
      if (!am.count(brr[i])) {
        printf("%d ", brr[i]);
      }
    }
    putchar('\n');
    for (int i = 0; i < m; i++) {
      if (!bm.count(arr[i])) {
        printf("%d ", arr[i]);
      }
    }
    putchar('\n');
  }
} 
