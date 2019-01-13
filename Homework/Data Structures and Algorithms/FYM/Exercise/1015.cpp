// 1015. Find outdegrees
#include <vector>
#include <list>
using namespace std;

struct ALGraph {
  vector<list<int> > adj; //adjacency list of the graph. adj[v] is the list of v's adjacent vertices.
  int vexnum;// number of vertices
  int arcnum;// number of edges
  //A simple initialization.
  ALGraph(int n=0):vexnum(n) {
    list<int> l;
    adj.resize(n);
    for (int i = 0; i<n; i++)
      adj[i] = l;
  }
};

#include <vector>
#include <list>
using namespace std;

vector<int> outdegree(const ALGraph &g) {
  vector<int> v;
  for (auto &i: g.adj) {
    v.push_back(i.size());
  }
  return v;
}

int main() {}
