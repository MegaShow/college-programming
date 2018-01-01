// 1005. 业绩排名
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<pair<int, string> >bonusList(vector<pair<string, int> > v) {
  stable_sort(v.begin(), v.end(), [](pair<string, int> a, pair<string, int> b) -> bool {
    return a.second > b.second;
  });
  vector<pair<int, string> > vtmp;
  if (v.size() == 0) return vtmp;
  int prev_score = v[0].second;
  int level = 1;
  for (int i = 0; i < v.size(); i++) {
    if (v[i].second != prev_score) {
      prev_score = v[i].second;
      level++;
    }
    vtmp.push_back(make_pair(level, v[i].first));
  }
  return vtmp;
}

#include <iostream>
using namespace std;
int main() {
  vector<pair<string, int> > v = { {"wang ming", 320}, {"gao min", 330}, {"zhang li", 280}, {"luo yan", 320} };
  vector<pair<int, string> > vtmp = bonusList(v);
  for (auto &i: vtmp) {
    cout << i.first << ',' << i.second << endl;
  }
}
