// 1006. Printer Queue
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main() {
  int num, n, m, var;
  cin >> num;
  while (num--) {
    queue<pair<int, bool> > q;
    vector<int> v;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> var;
      if (i == m) {
        q.push(make_pair(var, true));
      } else {
        q.push(make_pair(var, false));
      }
      v.push_back(var);
    }
    sort(v.begin(), v.end());
    int out = 0;
    while (!q.empty()) {
      if (v.back() != q.front().first) {
        pair<int, bool> n = q.front();
        q.pop();
        q.push(n);
      } else {
        out++;
        if (q.front().second == true) {
          break;
        }
        q.pop();
        v.pop_back();
      }
    }
    cout << out << endl;
  }
}
