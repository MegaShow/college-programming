// 1004. shortest path in unweighted graph
#include <iostream>
#include <map>
#include <set>
#include <queue>
using namespace std;

int main() {
  int n, m, vala, valb;
  map<int, set<int> > edge;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> vala >> valb;
    edge[vala].insert(valb);
    edge[valb].insert(vala);
  }
  queue<int> q;
  map<int, int> distance;
  set<int> visit;
  q.push(1);
  while (!q.empty()) {
    int nq = q.front();
    q.pop();
    if (edge.count(nq) && !visit.count(nq)) {
      visit.insert(nq);
      for (auto &i: edge[nq]) {
        q.push(i);
        if (!distance.count(i) || distance[i] > distance[nq]) {
          distance[i] = distance[nq] + 1;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (distance.count(i)) cout << distance[i] << ' ';
    else cout << -1 << ' ';
  }
  cout << endl;
}
