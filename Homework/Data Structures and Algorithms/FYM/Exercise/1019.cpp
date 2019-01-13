// 1019. 社交距离
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int Dijkstra(int a, int b, bool* graph, int vertice);

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int vertice, edge, a, b;
    cin >> vertice >> edge >> a >> b;
    bool graph[vertice * vertice];
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < edge; i++) {
      int s, e;
      cin >> s >> e;
      graph[s * vertice + e] = graph[e * vertice + s] = true;
    }
    cout << Dijkstra(a, b, graph, vertice) << endl;
  }
}

int Dijkstra(int a, int b, bool* graph, int vertice) {
  bool visit[vertice];
  memset(visit, 0, sizeof(visit));
  queue<pair<int, int> > q;
  q.push(make_pair(a, 0));
  while (!q.empty()) {
    pair<int, int> nq = q.front();
    q.pop();
    visit[nq.first] = true;
    if (graph[nq.first * vertice + b]) return nq.second + 1;
    for (int i = 0; i < vertice; i++) {
      if (visit[i] == false && graph[nq.first * vertice + i]) q.push(make_pair(i, nq.second + 1));
    }
  }
  return -1;
}