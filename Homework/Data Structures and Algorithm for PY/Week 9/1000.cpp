// 1000. 堆排序
#include <functional>
#include <cstdio>
using namespace std;

void HeapSort(int* arr, int size) {
  auto PrintHeap = [] (int* arr, int size) {
    if (size > 0) {
      printf("%d", arr[0]);
      for (int i = 1; i < size; i++) {
        printf(" %d", arr[i]);
      }
      printf("\n");
    }
  };

  function<void(int*, int, int)> HeapAdjust = [&] (int* arr, int index, int size) {
    if (index < size / 2) {
      int left = index * 2 + 1;
      int right = index * 2 + 2;
      int max = index;
      if (left < size && right < size && arr[left] < arr[right]) {
        max = right;
      } else if (left < size && right < size && arr[left] >= arr[right]) {
        max = left;
      } else if (left < size && right >= size) {
        max = left;
      }
      if (arr[index] < arr[max]) {
        arr[index] = arr[index] ^ arr[max];
        arr[max] = arr[index] ^ arr[max];
        arr[index] = arr[index] ^ arr[max];
        HeapAdjust(arr, max, size);
      }
    }
  };

  for (int i = size / 2; i >= 0; i--) {
    HeapAdjust(arr, i, size);
  }
  for (int i = size - 1; i >= 0; i--) {
    PrintHeap(arr, size);
    if (i) {
      arr[i] = arr[0] ^ arr[i];
      arr[0] = arr[0] ^ arr[i];
      arr[i] = arr[0] ^ arr[i];
      HeapAdjust(arr, 0, i);
    }
  }
}

int main() {
  int n;
  while (~scanf("%d", &n)) {
    int arr[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
    }
    HeapSort(arr, n);
  }
}
