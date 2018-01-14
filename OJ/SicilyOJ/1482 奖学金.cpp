// 1004. 奖学金
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n, chinese, english, math;
  bool flag = false;
  while (cin >> n) {
    vector<pair<int, pair<int, int> > > v;
    for (int i = 1; i <= n; i++) {
      cin >> chinese >> math >> english;
      v.push_back(make_pair(i, make_pair(chinese + math + english, chinese)));
    }
    sort(v.begin(), v.end(), [](pair<int, pair<int, int> > a, pair<int, pair<int, int> > b) -> bool {
      return a.second.first > b.second.first || (a.second.first == b.second.first && a.second.second > b.second.second) ||
        (a.second.first == b.second.first && a.second.second == b.second.second && a.first < b.first);
    });
    if (flag) {
      cout << endl;
    }
    flag = true;
    for (int i = 0; i < 5; i++) {
      cout << v[i].first << ' ' << v[i].second.first << endl;
    }
  }
}