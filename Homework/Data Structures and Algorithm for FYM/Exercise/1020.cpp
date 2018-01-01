// 1020. 机器产量
#include <iostream>
#include <map>
using namespace std;

int main() {
  int t, n, id, val;
  cin >> t;
  while (t--) {
    map<int, int> m;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> id >> val;
      if (m.count(id)) {
        if (m[id] < val) m[id] = val;
      } else {
        m[id] = val;
      }
    }
    for (auto &i: m) {
      cout << i.first << ' ' << i.second << endl;
    }
  }
}
