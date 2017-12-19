// 1005. 数组的合并
#include <iostream>
using namespace std;

int main() {
  int arr[2][5];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> arr[i][j];
    }
  }
  int index0 = 0, index1 = 0;
  while (index0 < 5 && index1 < 5) {
    if (arr[0][index0] <= arr[1][index1]) {
      cout << arr[0][index0++] << ' '; 
    } else {
      cout << arr[1][index1++] << ' ';
    }
  }
  while (index0 < 5) {
    cout << arr[0][index0++] << ' ';
  }
  while (index1 < 5) {
    cout << arr[1][index1++] << ' ';
  }
}
