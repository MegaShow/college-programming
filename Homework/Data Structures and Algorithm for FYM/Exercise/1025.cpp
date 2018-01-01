// 1025. 求四分位数
#include <vector>
#include <algorithm>
using namespace std;

pair<double, int> Q1(vector<double> v) {
  sort(v.begin(), v.end());
  return make_pair(v[v.size() / 4], v.size() / 4);
}

#include <iostream>

int main() {
  vector<double> v = {1,2,3,2,3,2,4};
  auto val = Q1(v);
  cout << val.first << ',' << val.second << endl;
}
