// 1002. 贫富差距
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int m, n, k, var, max, min;
  cin >> m;
  while (m--) {
    vector<int> v;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
      cin >> var;
      v.push_back(var);
    }
    sort(v.begin(), v.end());
    if ((k & 1) == 0) {
      min = (v[k/2-1] + v[k/2]) / 2;   // 0 ~ (k-1)
      max = (v[n-k/2-1] + v[n-k/2]) / 2; // (n-k+1) ~ n
    } else {
      min = v[k/2];
      max = v[n-k/2-1];
    }
    cout << max - min << endl;
  }
}
