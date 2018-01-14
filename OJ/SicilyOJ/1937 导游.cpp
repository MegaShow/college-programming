// 1937. 导游
#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int n, edge;
    cin >> n >> edge;
    int graph[n+1][n+1];
    int dis[n+1];
    memset(dis, 0, sizeof(dis));
    memset(graph, 0, sizeof(int) * (n + 1) * (n + 1));
    for (int i = 0; i < edge; i++) {
      int a, b, val;
      cin >> a >> b >> val;
      graph[a][b] = graph[b][a] = val;
    }
    int start, end, tourist;
    cin >> start >> end >> tourist;
    queue<int> q;
    q.push(start);
    while (q.size()) {
      int nq = q.front();
      q.pop();
      for (int i = 1; i <= n; i++) {
        if (i == nq || dis[i] >= graph[nq][i] || graph[nq][i] == 0) continue;
        if (dis[i] < dis[nq]) {
          dis[i] = graph[nq][i] < dis[nq] ? graph[nq][i] : dis[nq];
          q.push(i);
        } else if (dis[i] == 0) {
          dis[i] = graph[nq][i];
          q.push(i);
        }
      }
      /* cout << nq << " => ";
      for (int i = 1; i <= n; i++) {
        cout << dis[i] << ' ';
      }
      cout << endl; */
    }
    cout << (tourist + dis[end] - 2) / (dis[end] - 1) << endl;
  }
}
