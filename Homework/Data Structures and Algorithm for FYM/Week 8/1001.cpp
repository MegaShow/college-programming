// 1001. binary search
// the function search in an ordered vector table between bot and top (inclusive) for x.
// It returns the index of its last oocurrence if search is successful, it returns -1 if search is unsuccessful.
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
int binarySearch(const vector<T> &v, int low, int high, const T &value) {
  if (low == high && value == v[low]) {
    return high;
  } else if (low == high) {
    return -1;
  }
  int index = (high - low) / 2 + low + 1;
  if (v[index] > value) {
    return binarySearch(v, low, index - 1, value);
  } else {
    return binarySearch(v, index, high, value);
  }
}

int main() {
  int a[ ] = {0,1, 1,3,3,3,6};
  
  vector<int> v(a,a+7);
  
  cout << binarySearch(v, 0, v.size()-1, 3);  // 输出5
  
  cout << binarySearch(v, 0, v.size()-1, 7);  //输出-1
}