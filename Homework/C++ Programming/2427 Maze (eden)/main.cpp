// MegeShow
#include <iostream>
#include <queue>
using namespace std;


int main() {
    int var = 0;
    bool error = true;
    int n, m, x, y;
    cin >> n >> m;
    char map[n][m];
    bool flag[n][m];
    cin.get();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin.get(map[i][j]);
            flag[i][j] = false;
            if(map[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
        cin.get();
    }
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }*/

    // BFS
    queue<pair<int, int> > nq;
    queue<int> step;
    nq.push(make_pair(x, y));
    step.push(0);
    while(nq.empty() == false) {
        pair<int, int> n = nq.front();
        var = step.front();
        nq.pop();
        step.pop();
        if(map[n.first][n.second] == 'E') {
            error = false;
            break;
        }
        if(flag[n.first-1][n.second] == false && (map[n.first-1][n.second] == '.' || map[n.first-1][n.second] == 'E')) {
            nq.push(make_pair(n.first-1, n.second));
            step.push(var+1);
            flag[n.first-1][n.second] = true;
        }
        if(flag[n.first][n.second-1] == false && (map[n.first][n.second-1] == '.' || map[n.first][n.second-1] == 'E')) {
            nq.push(make_pair(n.first, n.second-1));
            step.push(var+1);
            flag[n.first][n.second-1] = true;
        }
        if(flag[n.first+1][n.second] == false && (map[n.first+1][n.second] == '.' || map[n.first+1][n.second] == 'E')) {
            nq.push(make_pair(n.first+1, n.second));
            step.push(var+1);
            flag[n.first+1][n.second] = true;
        }
        if(flag[n.first][n.second+1] == false && (map[n.first][n.second+1] == '.' || map[n.first][n.second+1] == 'E')) {
            nq.push(make_pair(n.first, n.second+1));
            step.push(var+1);
            flag[n.first][n.second+1] = true;            
        }
    }
    if(error) {
        cout << -1 << endl;
    }
    else {
        cout << var << endl;
    }
}