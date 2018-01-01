// 1031. Easy sort
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int t, n, val;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      cin >> val;
      v.push_back(val);
    }
    sort(v.begin(), v.end());
    for (auto &i: v) {
      cout << i << endl;
    }
  }
}
