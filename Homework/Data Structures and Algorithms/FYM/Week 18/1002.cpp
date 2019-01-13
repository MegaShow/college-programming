// 1002. 畅通工程
#include <iostream>
#include <cstring>
using namespace std;

void Dijkstra(int** graph, int dis[], int num, int start, int end);
void Floyd(int** graph, int dis[], int num, int start);

int main() {
  int num, edge, a, b, val;
  while (cin >> num >> edge) {
    int** graph;
    int dis[num];
    graph = new int*[num];
    for (int i = 0; i < num; i++) {
      graph[i] = new int[num];
      memset(graph[i], -1, sizeof(int) * num);
      graph[i][i] = 0;
    }
    for (int i = 0; i < edge; i++) {
      cin >> a >> b >> val;
      if (graph[a][b] == -1 || graph[a][b] > val) {
        graph[a][b] = graph[b][a] = val;
      }
    }
    cin >> a >> b;
    // Dijkstra(graph, dis, num, a, b);
    Floyd(graph, dis, num, a);
    cout << dis[b] << endl;
    for (int i = 0; i < num; i++) {
      delete [] graph[i];
    }
    delete [] graph;
  }
}

void Dijkstra(int** graph, int dis[], int num, int start, int end) {
  bool visit[num];
  memset(visit, 0, sizeof(visit));
  memset(dis, -1, sizeof(int) * num);
  visit[start] = true;
  dis[start] = 0;
  for (int i = 0; i < num; i++) {
    if (graph[start][i] != -1) dis[i] = graph[start][i];
  }
  for (int i = 1; i < num; i++) {
    int min = -1;
    for (int j = 0; j < num; j++) {
      if (visit[j]) continue;
      if (dis[j] != -1 && (min == -1 || dis[min] > dis[j])) {
        min = j;
      }
    }
    if (min == -1 || min == end) return;
    visit[min] = true;
    for (int j = 0; j < num; j++) {
      if (graph[min][j] == -1) continue;
      if (dis[j] == -1 || dis[j] > dis[min] + graph[min][j]) {
        dis[j] = dis[min] + graph[min][j];
      }
    }
  }
}

void Floyd(int** graph, int dis[], int num, int start) {
  memset(dis, -1, sizeof(int) * num);
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      for (int k = 0; k < num; k++) {
        if (graph[j][i] == -1 || graph[k][i] == -1) continue;
        if (graph[j][k] == -1 || graph[j][k] > graph[j][i] + graph[k][i]) {
          graph[j][k] = graph[k][j] = graph[j][i] + graph[k][i];
        }
      }
    }
  }
  for (int i = 0; i < num; i++) {
    dis[i] = graph[start][i];
  }
}
