// 1002. 寻找前k大的数
#include <cstdio>
using namespace std;

void qSortByK(int* arr, int start, int end, int k) {
  if (start >= end - 1) {
    return;
  }
  int var = arr[start];
  int left = start, right = end - 1;
  while (left < right) {
    while (left < right && arr[right] <= var) {
      right--;
    }
    arr[left] = arr[right];
    while (left < right && arr[left] >= var) {
      left++;
    }
    arr[right] = arr[left];
  }
  arr[left] = var;
  qSortByK(arr, start, left, k);
  if (left < k) {
    qSortByK(arr, left + 1, end, k);
  }
}

int main() {
  int n, k;
  while (~scanf("%d%d", &n, &k)) {
    int arr[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
    }
    k--;
    qSortByK(arr, 0, n, k);
    for (int i = 0; i < k; i++) {
      printf("%d ", arr[i]);
    }
    printf("%d\n", arr[k]);
  }
}
