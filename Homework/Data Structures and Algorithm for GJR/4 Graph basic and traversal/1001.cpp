// 1001. Forest
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int getMaxValueFromMap(const map<int, int>& m);

int main() {
  int n, m, vals, vale;
  cin >> n >> m;
  while (n) {
    vector<pair<int, int> > edge;
    map<int, int> from_m;
    map<int, vector<int> > to_m;
    map<int, int> height;
    map<int, int> width;
    int unionFind[n+1];
    bool isValid = true;
    for (int i = 1; i <= n; i++) {
      unionFind[i] = i;
    }
    for (int i = 0; i < m; i++) {
      cin >> vals >> vale;
      edge.push_back(make_pair(vals, vale));
    }
    for (auto &i: edge) {
      if (from_m.count(i.second) || i.first == i.second || unionFind[i.first] == unionFind[i.second]) {
        isValid = false;
        break;
      }
      from_m[i.second] = i.first;
      to_m[i.first].push_back(i.second);
      int val = unionFind[i.second];
      for (int j = 1; j <= n; j++) {
        if (unionFind[j] == val) unionFind[j] = unionFind[i.first];
      }
    }
    if (!isValid) cout << "INVALID" << endl;
    else {
      queue<int> q;
      for (int i = 1; i <= n; i++) {
        if (!from_m.count(i)) q.push(i);
      }
      while (!q.empty()) {
        int ntop = q.front();
        width[height[ntop]]++;
        q.pop();
        if (to_m.count(ntop)) {
          for (auto &i: to_m[ntop]) {
            q.push(i);
            height[i] = height[ntop] + 1;
          }
        }
      }
      cout << getMaxValueFromMap(height) << ' ' << getMaxValueFromMap(width) << endl;
    }
    cin >> n >> m;
  }
}

int getMaxValueFromMap(const map<int, int>& m) {
  map<int, int, greater<int> > tmp;
  for (auto &i: m) {
    tmp.insert(make_pair(i.second, i.first));
  }
  return tmp.begin()->first;
}
