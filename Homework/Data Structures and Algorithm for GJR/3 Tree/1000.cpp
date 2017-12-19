// 1000. 完全二叉树
#include <cstdio>
using namespace std;

int GetRoot(int x, int y) {
  if (x == y) {
    return x;
  } else if (x > y) {
    return GetRoot(x >> 1, y);
  } else {
    return GetRoot(x, y >> 1);
  }
}

int main() {
  int t, a, b;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &a, &b);
    printf("%d\n", GetRoot(a, b));
  }
}
