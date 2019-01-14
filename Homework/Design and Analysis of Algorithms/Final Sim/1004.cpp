// 1004. Play The Game
#include <iostream>
#include <limits>
#include <map>

using namespace std;

int dfs(map<unsigned, int> &m, int** val, unsigned key, int len, const unsigned limit) {
    if (m.count(key)) {
        return m[key];
    }
    if (key == limit) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if ((key >> i & 1) == 1) {
            continue;
        }
        key |= (1 << i);
        key += (1 << len);
        int v = dfs(m, val, key, len, limit);
        key ^= (1 << i);
        key -= (1 << len);
        if (v + val[key >> len][i] > m[key]) {
            m[key] = v + val[key >> len][i];
        }
    }
    return m[key];
}

int main() {
    int caseNum, num;
    cin >> caseNum;
    while (caseNum--) {
        cin >> num;
        int **val = new int*[num];
        for (int i = 0; i < num; i++) {
            val[i] = new int[num];
            for (int j = 0; j < num; j++) {
                cin >> val[i][j];
            }
        }
        map<unsigned, int> m; // key: 状态, value: 最优解
        cout << dfs(m, val, 0, num, (1 << num) - 1 + (num << num)) << endl;
        for (int i = 0; i < num; i++) {
            delete [] val[i];
        }
        delete [] val;
    }
}
