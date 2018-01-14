// 1641. Binary Searchable
#include <iostream>
#include <cstring>
using namespace std;

int main() {
  int num;
  while (cin >> num) {
    int arr[num];
    int max = 0;
    int min = 0;
    bool searchable[num];
    int sum = 0;
    memset(searchable, 0, sizeof(searchable));
    for (int i = 0; i < num; i++) {
      cin >> arr[i];
      if (i == 0 || max < arr[i]) {
        searchable[i] = true;
        max = arr[i];
      }
    }
    for (int i = num - 1; i >= 0; i--) {
      if (i == num - 1 || min > arr[i]) {
        min = arr[i];
      } else {
        searchable[i] = false;
      }
      sum += searchable[i];
    }
    cout << sum << endl;
  }
}
