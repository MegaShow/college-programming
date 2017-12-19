// MegaShow
#include <iostream>
#include <queue>
using namespace std;

int main() {
    int c, n, m, var;
    cin >> c;
    for (int i = 0; i < c; i++) {
        cin >> n >> m;
        priority_queue<int> p;
        queue<pair<int, bool> > q;
        for (int j = 0; j < n; j++) {
            cin >> var;
            if (j == m) {
                p.push(var);
                q.push(make_pair(var, true));
            } else {
                p.push(var);
                q.push(make_pair(var, false));
            }
        }
        var = 0;
        while (!q.empty()) {
            pair<int, bool> nq = q.front();
            int np = p.top();
            q.pop();
            if (np > nq.first) {
                q.push(nq);
            } else if (np == nq.first) {
                p.pop();
                var++;
                if (nq.second) {
                    cout << var << endl;
                    break;
                }
            } else {
                cout << "error" << endl;
            }
        }
    }
}
