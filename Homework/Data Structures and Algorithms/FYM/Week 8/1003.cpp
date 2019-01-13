// 1003. 选择排序
#include <iostream>
using namespace std;

int main() {
  int num, var;
  cin >> num;
  while (num--) {
    cin >> var;
    int arr[var];
    for (int i = 0; i < var; i++) {
      cin >> arr[i];
    }
    for (int i = 0; i < var - 1; i++) {
      int min = i;
      for (int j = i + 1; j < var; j++) {
        if (arr[j] < arr[min]) {
          min = j;
        }
      }
      int tmp = arr[min];
      arr[min] = arr[i];
      arr[i] = tmp;
      for (int j = 0; j < var - 1; j++) {
        cout << arr[j] << ' ';
      }
      cout << arr[var-1] << endl;
    }
  }
}
