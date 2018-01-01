// 1306. Sorting Algorithm
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n, m, val;
  cin >> n >> m;
  while (n != 0) {
    vector<int> v;
    for (int i = 0; i < n; i++) {
      cin >> val;
      v.push_back(val);
    }
    sort(v.begin(), v.end());
    if (v.size()) {
      cout << v[0];
    }
    for (int i = m; i < v.size(); i = i + m) {
      cout << ' ' << v[i];
    }
    cout << endl;
    cin >> n >> m;
  }
}
