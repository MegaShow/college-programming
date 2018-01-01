// 1001. Bacon Number
#include <iostream>
#include <map>
#include <set>
using namespace std;

void Dijkstra(map<int, set<int> >& graph, map<int, int>& distance);

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int edge_num;
    cin >> edge_num;
    map<int, set<int> > relation;
    map<int, int> distance;
    for (int i = 0; i < edge_num; i++) {
      int actor_a, actor_b;
      cin >> actor_a >> actor_b;
      relation[actor_a].insert(actor_b);
      relation[actor_b].insert(actor_a);
    }
    Dijkstra(relation, distance);
    for (auto &i: distance) {
      if (i.first == 0) continue;
      cout << i.first << ':' << i.second << endl;
    }
    cout << "---" << endl;
  }
}

void Dijkstra(map<int, set<int> >& graph, map<int, int>& distance) {
  for (auto &to: graph[0]) {
    distance[to] = 1;
  }
  set<int> visit;
  visit.insert(0);
  for (int i = 1; i < graph.size(); i++) {
    int to = 0;
    for (auto &to_item: graph[0]) {
      if (!visit.count(to_item)) {
        to = to_item;
        break;
      }
    }
    if (to == 0) break;
    visit.insert(to);
    graph[0].erase(to);
    for (auto &i: graph[to]) {
      graph[0].insert(i);
    }
    for (auto &relation: graph[to]) {
      if (!distance.count(relation) || distance[relation] > distance[to] + 1) {
        distance[relation] = distance[to] + 1;
      }
    }
  }
}
