// 1000. 连通性问题
#include <iostream>
using namespace std;

int unionFind[100001];

int find(int val) {
  if (val == unionFind[val]) return val;
  unionFind[val] = find(unionFind[val]);
  return unionFind[val];
}

int main() {
  int a, b;
  for (int i = 0; i < 100001; i++) {
    unionFind[i] = i;
  }
  while (cin >> a >> b) {
    if (find(a) != find(b)) {
      cout << a << ' ' << b << endl;
      unionFind[find(a)] = unionFind[find(b)];
    }
  }
}
