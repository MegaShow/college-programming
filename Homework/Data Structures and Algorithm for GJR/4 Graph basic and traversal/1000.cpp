// 1000. Knight Moves
#include <iostream>
#include <queue>
using namespace std;

int direct[8][2] = {
  { -1, -2 }, { 1, -2 }, { 2, -1 }, { 2, 1 },
  { 1, 2 }, { -1, 2 }, { -2, 1 }, { -2, -1 }
};

int main() {
  int t;
  cin >> t;
  while (t--) {
    pair<int, int> start, end;
    char sx, sy, ex, ey, c;
    cin >> sx >> sy >> ex >> ey;
    start = make_pair(sx - 'a', sy - '1');
    end = make_pair(ex - 'a', ey - '1');
    queue<pair<int, pair<int, int> > > q;
    q.push(make_pair(0, make_pair(start.first, start.second)));
    while (!q.empty()) {
      pair<int, pair<int, int> > nq = q.front();
      q.pop();
      if (nq.second == end) {
        cout << "To get from " << sx << sy << " to " << ex << ey << " takes " << nq.first << " knight moves." << endl;
        break;
      }
      for (int i = 0; i < 8; i++) {
        int newx = nq.second.first + direct[i][0];
        int newy = nq.second.second + direct[i][1];
        if (newx >= 0 && newx < 8 && newy >= 0 && newy < 8) {
          q.push(make_pair(nq.first + 1, make_pair(newx, newy)));
        }
      }
    }
  }
}
