// 1001. Highways
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int unionSet[500];

int find(int val) {
  if (val == unionSet[val]) return val;
  unionSet[val] = find(unionSet[val]);
  return unionSet[val];
}

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int n, val;
    cin >> n;
    for (int i = 0; i < n; i++) {
      unionSet[i] = i;
    }
    vector<pair<int, pair<int, int> > > v;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> val;
        if (i < j) {
          v.push_back(make_pair(val, make_pair(i, j)));
        }
      }
    }
    sort(v.begin(), v.end(), [](pair<int, pair<int, int> > a, pair<int, pair<int, int> > b) -> bool {
      return a.first < b.first;
    });
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
      if (count == n - 1) break;
      if (find(v[i].second.first) != find(v[i].second.second)) {
        count++;
        unionSet[find(v[i].second.first)] = unionSet[find(v[i].second.second)];
        if (count == n - 1) {
          cout << v[i].first << endl;
          if (case_num) cout << endl;
          break;
        }
      }
    }
  }
}
