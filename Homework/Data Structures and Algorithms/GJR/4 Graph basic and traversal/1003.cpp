// 1003. connect components in undirected graph
#include <iostream>
#include <set>
using namespace std;

int main() {
  int node, edge, na, nb;
  cin >> node >> edge;
  int unionFind[node + 1];
  for (int i = 0; i <= node; i++) {
    unionFind[i] = i;
  }
  for (int i = 0; i < edge; i++) {
    cin >> na >> nb;
    int val = unionFind[na];
    for (int j = 1; j <= node; j++) {
      if (unionFind[j] == val) unionFind[j] = unionFind[nb];
    }
  }
  set<int> s;
  for (int i = 1; i <= node; i++) {
    s.insert(unionFind[i]);
  }
  cout << s.size() << endl;
}
