// MegaShow
#include <iostream>
#include <climits>
#include <queue>
using namespace std;


// 使用广度优先搜索对节点分层次，同时判断是否还能形成从源到汇的路径
bool bfs(int** flow, int* level, const int vertice) {
    for (int i = 1; i < vertice; i++) {
        level[i] = 0;
    }
    queue<pair<int, int> > nq;  // (vertice, level)
    nq.push(make_pair(0, 0));
    while (!nq.empty()) {
        pair<int, int> n = nq.front();
        nq.pop();
        for (int i = 1; i < vertice; i++) {
            if  (level[i] == 0 && flow[n.first][i] > 0) {
                nq.push(make_pair(i, n.second + 1));
                level[i] = n.second + 1;
            }
        }
    }
    return level[vertice-1];
}


// 使用深度优先搜索获取增流路径，并获取最大的增流
int dfs(int** flow, int* level, const int vertice, int x, int cut_flow) {
    if (x == vertice - 1) {
        return cut_flow;
    }
    for (int i = 1; i < vertice; i++) {
        if (flow[x][i] > 0 && level[x] + 1 == level[i]) {
            int min = (cut_flow > flow[x][i] ? flow[x][i] : cut_flow);
            int var = dfs(flow, level, vertice, i, min);
            if (var > 0) {
                flow[x][i] -= var;
                flow[i][x] += var;
                return var;
            }
        }
    }
    return 0;
}


int main() {
    int vertice, edge;
    cin >> vertice >> edge;
    int** flow = new int*[vertice];   // 储存容量
    int* level = new int[vertice];    // 储存节点层次
    for (int i = 0; i < vertice; i++) {
        flow[i] = new int[vertice];
        for (int j = 0; j < vertice; j++) {
            flow[i][j] = 0;
        }
    }
    for (int i = 0; i < edge; i++) {
        int a, b, f;
        cin >> a >> b >> f;
        flow[a][b] = f;
    }
    int out = 0;
    // 先对节点分层次，再增流
    while (bfs(flow, level, vertice)) {
        int ret;
        while (ret = dfs(flow, level, vertice, 0, INT_MAX)) {
            out += ret;
        }
    }
    cout << out << endl;
}
