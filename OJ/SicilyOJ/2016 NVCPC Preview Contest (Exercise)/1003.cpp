// 1003. Tailmon with God Ye
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  vector<int> v;
  int val;
  cin >> val;
  for (int i = 0; i < val; i++) {
    int tmp;
    cin >> tmp;
    v.push_back(tmp);
  }
  sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
  if (v[0] > 2) v[0] = 2;
  int sum = 0;
  for (auto &i: v) {
    sum = sum + i;
  }
  cout << sum << endl;
}
