// 1001. 快速排序
#include <iostream>
using namespace std;

template <class Record> 
void quick_sort(Record* startPointer, Record* endPointer) {
  if (startPointer < endPointer) {
    Record base = *startPointer;
    Record* left = startPointer;
    Record* right = endPointer - 1;
    while (left != right) {
      while (left != right && *right >= base) {
        right--;
      }
      *left = *right;
      while (left != right && *left <= base) {
        left++;
      }
      *right = *left;
    }
    *left = base;
    quick_sort(startPointer, left);
    quick_sort(left + 1, endPointer);
  }
}

int main() {
  int arr[10];
  for (int i = 9; i >= 0; i--) {
    arr[9-i] = i;
  }
  quick_sort(arr, arr + 10);
  for (int i = 0; i < 10; i++) {
    cout << arr[i];
  }
}
