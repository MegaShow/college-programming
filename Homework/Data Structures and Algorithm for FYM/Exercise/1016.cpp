// 1016. 度序列
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int t, n, val;
  cin >> t;
  while (t--) {
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int sum = 0;
      for (int j = 0; j < n; j++) {
        cin >> val;
        sum = sum + val;
      }
      v.push_back(sum);
    }
    sort(v.begin(), v.end(), [](int a, int b) {
      return a > b;
    });
    for (int i = 0; i < v.size(); i++) {
      cout << v[i] << ' ';
    }
    cout << endl;
  }
}
