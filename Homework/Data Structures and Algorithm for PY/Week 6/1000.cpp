// 1000. 迷宫深度优先搜索
#include <iostream>
#include <vector>
using namespace std;

const int step[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void dfs(bool** arr, pair<int, int> pos, pair<int, int> exit_pos, bool& flag, vector<pair<int, int> >& v, bool** visit) {
  if (pos == exit_pos) {
    flag = true;
    return;
  }
  for (int i = 0; !flag && i < 4; i++) {
    int x = pos.first + step[i][0];
    int y = pos.second + step[i][1];
    if (x >= 0 && x <= exit_pos.first && y >= 0 && y <= exit_pos.second && arr[x][y] == 0 && visit[x][y] == 0) {
      visit[x][y] = 1;
      v.push_back(make_pair(x, y));
      dfs(arr, make_pair(x, y), exit_pos, flag, v, visit);
      if (flag) {
        return;
      }
      v.pop_back();
      visit[x][y] = 0;
    }
  }
}

int main() {
  int num, a, b;
  cin >> num;
  while (num--) {
    cin >> a >> b;
    bool** arr = new bool*[a];
    bool** visit = new bool*[a];
    for (int i = 0; i < a; i++) {
      arr[i] = new bool[b];
      visit[i] = new bool[b];
      cin.get();
      for (int j = 0; j < b; j++) {
        arr[i][j] = cin.get() - '0';
        visit[i][j] = false;
      }
    }
    vector<pair<int, int> > v;
    bool flag = false;
    if (arr[0][0] == 0 && arr[a-1][b-1] == 0) {
      visit[0][0] = 1;
      dfs(arr, make_pair(0, 0), make_pair(a-1, b-1), flag, v, visit);
    }
    if (flag) {
      cout << "(0,0)";
      for (auto &i : v) {
        cout << " (" << i.first << "," << i.second << ")";
      }
      cout << endl;
    } else {
      cout << "no" << endl;
    }
    for (int i = 0; i < a; i++) {
      delete [] arr[i];
    }
    delete [] arr;
  }
}
