// 1017. 计算二叉查找树的高度
#include <iostream>
using namespace std;

int parse(int pre[], int preIndex, int in[], int inIndex, int size, int height) {
  if (size == 0) return height;
  int lhs = 0;
  while (lhs < size) {
    if (pre[preIndex] == in[inIndex + lhs]) break;
    lhs++;
  }
  int a = parse(pre, preIndex + 1, in, inIndex, lhs, height + 1);
  int b = parse(pre, preIndex + 1 + lhs, in, inIndex + lhs + 1, size - lhs - 1, height + 1);
  return a > b ? a : b;
}

int main() {
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    int pre[n], in[n];
    for (int i = 0; i < n; i++) {
      cin >> pre[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> in[i];
    }
    cout << parse(pre, 0, in, 0, n, -1) << endl;
  }
}
