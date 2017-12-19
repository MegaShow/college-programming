// 1002. 马周游问题[Special judge]
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int step[8][2] = { {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1} };

int getNextNum(int now_x, int now_y, int visit[][8]) {
  int count = 0;
  for (int i = 0; i < 8; i++) {
    int x = now_x + step[i][0];
    int y = now_y + step[i][1];
    int next = x * 8 + y + 1;
    if (x >= 0 && x < 8 && y >= 0 && y < 8 && visit[x][y] == 0) {
      count++;
    }
  }
  return count;
}

vector<pair<int, pair<int, int> > > setNext(int now, int visit[][8]) {
  vector<pair<int, pair<int, int> > > next_step;
  for (int i = 0; i < 8; i++) {
    int x = (now - 1) / 8 + step[i][0];
    int y = (now - 1) % 8 + step[i][1];
    int next = x * 8 + y + 1;
    if (x >= 0 && x < 8 && y >= 0 && y < 8 && visit[x][y] == 0) {
      int s = getNextNum(x, y, visit);
      next_step.push_back(make_pair(s, make_pair(x, y)));
    }
  }
  sort(next_step.begin(), next_step.end(), [](pair<int, pair<int, int> > a, pair<int, pair<int, int> > b) -> bool {
    return a.first < b.first;
  });
  return next_step;
}

void dfs(vector<int>& v, int now, int visit[][8], bool& flag) {
  if (flag || v.size() == 63) {
    flag = true;
    return;
  }
  auto vs = setNext(now, visit);
  for (int i = 0; !flag && i < vs.size(); i++) {
    int x = vs[i].second.first;
    int y = vs[i].second.second;
    int next = x * 8 + y + 1;
    visit[x][y] = 1;
    v.push_back(next);
    dfs(v, next, visit, flag);
    if (flag) {
      return;
    }
    v.pop_back();
    visit[x][y] = 0;
  }
}

int main() {
  int var = 1;
  int arr[8][8], visit[8][8];
  cin >> var;
  while (var != -1) {
    vector<int> v;
    bool flag = false;
    memset(visit, 0, sizeof(visit));
    visit[(var-1)/8][(var-1)%8] = 1;
    dfs(v, var, visit, flag);
    if (flag) {
      cout << var;
      for (auto& i: v) {
        cout << " " << i;
      }
      cout << endl;
    }
    cin >> var;
  }
}
