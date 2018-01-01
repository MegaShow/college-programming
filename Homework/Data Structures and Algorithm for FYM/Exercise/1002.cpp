// 1002. Is It Acyclic
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

bool Topological(int n, vector<int> graph_from_to[], int indegree[]);

int main() {
  int case_num;
  scanf("%d", &case_num);
  while (case_num--) {
    int n, edge;
    scanf("%d%d", &n, &edge);
    vector<int> graph_from_to[n + 1];
    int indegree[n + 1];
    memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < edge; i++) {
      int from, to;
      scanf("%d%d", &from, &to);
      graph_from_to[from].push_back(to);
      indegree[to]++;
    }
    if (Topological(n, graph_from_to, indegree)) printf("It is acyclic.\n");
    else printf("There exists a cycle.\n");
  }
}

bool Topological(int n, vector<int> graph_from_to[], int indegree[]) {
  queue<int> degree_0_queue;
  int count = 0;
  for (int v = 1; v <= n; v++) {
    if (indegree[v] == 0) degree_0_queue.push(v);
  }
  while (!degree_0_queue.empty()) {
    int n = degree_0_queue.front();
    degree_0_queue.pop();
    count++;
    for (auto &i: graph_from_to[n]) {
      indegree[i]--;
      if (indegree[i] == 0) degree_0_queue.push(i);
    }
  }
  return count == n;
}
