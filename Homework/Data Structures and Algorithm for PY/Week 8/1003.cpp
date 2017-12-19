// 1003. 发邀请函
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
  int num, m, n, var, max;
  cin >> num;
  while (num--) {
    cin >> m >> n;
    vector<int> v;
    max = 0;
    for (int i = 0; i < m; i++) {
      cin >> var;
      if (var > max) {
        max = var;
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> var;
      v.push_back(var);
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
      if (v[i] == max) {
        cout << 50 * i << endl;
        break;
      }
    }
  }
}
