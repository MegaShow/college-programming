// 1002. 插入排序
#include <iostream>
using namespace std;

int main() {
  int num;
  cin >> num;
  int arr[num];
  for (int i = 0; i < num; i++) {
    cin >> arr[i];
  }
  for (int i = 0; i < num; i++) {
    int var = arr[i];
    if (i != 0 && var >= arr[i-1]) {
      continue;
    }
    for (int j = i; j >= 0; j--) {
      if (j - 1 >= 0 && arr[j-1] > var) {
        arr[j] = arr[j-1];
      } else if (j == 0) {
        arr[0] = var;
      } else {
        arr[j] = var;
        break;
      }
    }
    for (int j = 0; j < num; j++) {
      cout << arr[j] << ' ';
    }
    cout << endl;
  }
}