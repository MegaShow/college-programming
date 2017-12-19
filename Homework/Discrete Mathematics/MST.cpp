#include <iostream>
#include <map>
using namespace std;

int main() {
    int vertice, edge, a, b;
    double weight;
    cin >> vertice >> edge;
    int* cnt = new int [vertice];
    for (int i = 0; i < vertice; i++) {
        cnt[i] = i;
    }
    map<double, pair<int, int> > relation;
    for (int i = 0; i < edge; i++) {
        cin >> a >> b >> weight;
        relation[weight] = make_pair(a, b);
    }
    weight = 0;
    map<double, pair<int, int> >::iterator it = relation.begin();
    while (it != relation.end()) {
        if (cnt[it->second.first] != cnt[it->second.second]) {
            weight += it->first;
            int var = cnt[it->second.second];
            for (int i = 0; i < vertice; i++) {
                if (cnt[i] == var) {
                    cnt[i] = cnt[it->second.first];
                }
            }
        }
        it++;
    }
    cout << weight << endl;
    delete [] cnt;
}