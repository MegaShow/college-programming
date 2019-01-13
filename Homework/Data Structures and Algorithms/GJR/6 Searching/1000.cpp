// 1000. Binary Search
int binSearch(const int s[], const int size, const int target) {
  int begin = 0, end = size, index;
  while (begin != end - 1) {
    index = (end - begin) / 2 + begin;
    if (s[index] <= target) begin = index;
    else end = index;
  }
  return s[begin] == target ? begin : -1;
}

int binSearchWithRecursion(const int s[], const int size, const int target) {
  if (size == 1) return s[0] == target ? 0 : -1;
  int index = size / 2;
  if (s[index] <= target) {
    int result = binSearch(s + index, size - index, target);
    return result != -1 ? index + result : -1;
  } else {
    return binSearch(s, index, target);
  }
}

#include <iostream>
using namespace std;
int main() {
  int s[8] = {0,1,1,3,3,3,6,6};
  cout << binSearch(s,8,3) << endl;  //输出5
  cout << binSearch(s,8,4) << endl;  //输出-1
}
