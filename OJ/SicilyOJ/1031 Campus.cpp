// 1031. Campus
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
using namespace std;

void Dijkstra(int graph[250][250], int dis[], int num, int start, int end);

int main() {
  int case_num, road_num, val;
  string stra, strb;
  cin >> case_num;
  while (case_num--) {
    cin >> road_num;
    map<string, int> symbol;
    int graph[250][250];
    int distance[250] = {0};
    int index = 0;
    memset(graph, -1, sizeof(int) * 250 * 250);
    for (int i = 0; i < road_num; i++) {
      cin >> stra >> strb >> val;
      if (!symbol.count(stra)) symbol[stra] = index++;
      if (!symbol.count(strb)) symbol[strb] = index++;
      int a = symbol[stra];
      int b = symbol[strb];
      if (graph[a][b] == -1 || graph[a][b] > val) {
        graph[a][b] = graph[b][a] = val;
      }
    }
    cin >> stra >> strb;
    if (stra == strb) {
      cout << 0 << endl;
    } else if (symbol.count(stra) && symbol.count(strb)) {
      // cout << "StrA: " << symbol[stra] << " StrB: " << symbol[strb] << endl;
      Dijkstra(graph, distance, symbol.size(), symbol[stra], symbol[strb]);
      cout << distance[symbol[strb]] << endl;
    } else {
      cout << -1 << endl;
    }
  }
}

void Dijkstra(int graph[250][250], int dis[250], int num, int start, int end) {
  bool visit[250];
  memset(visit, 0, sizeof(bool) * 250);
  memset(dis, -1, sizeof(int) * 250);
  dis[start] = 0;
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
      if (graph[min][j] == -1 || visit[j]) continue;
      if (dis[j] == -1 || dis[j] > dis[min] + graph[min][j]) {
        dis[j] = dis[min] + graph[min][j];
      }
    }
  }
}
