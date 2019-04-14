class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest.size() == 0 || forest[0][0] == 0) return -1;
        vector<vector<int>> trees; // { val, x, y }
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest[i].size(); j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({ forest[i][j], i, j });
                }
            }
        }
        sort(trees.begin(), trees.end(), [](vector<int>& a, vector<int>& b){
            return a[0] < b[0];
        });
        int x = 0, y = 0, res = 0;
        for (int i = 0; i < trees.size(); i++) {
            int d = bfs(forest, x, y, trees[i][1], trees[i][2]);
            if (d < 0) return -1;
            res += d;
            x = trees[i][1];
            y = trees[i][2];
        }
        return res;
    }

private:
    const int dir[4][2] = {
        { -1,  0 },
        {  0, -1 },
        {  0,  1 },
        {  1,  0 }
    };

    int bfs(vector<vector<int>>& forest, int sx, int sy, int dx, int dy) {
        if (sx == dx && sy == dy) return 0;
        int m = forest.size(), n = forest[0].size();
        vector<vector<int>> visit(m, vector<int>(n, 0));
        queue<pair<int, int>> q; // { x, y }
        q.push(make_pair(sx, sy));
        visit[sx][sy] = 1;
        int step = 0;
        while (!q.empty()) {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                pair<int, int> nq = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    int x = nq.first + dir[d][0];
                    int y = nq.second + dir[d][1];
                    if (x < 0 || x >= m || y < 0 || y >= n || visit[x][y] == 1 || forest[x][y] == 0) continue;
                    if (x == dx && y == dy) return step;
                    visit[x][y] = 1;
                    q.push(make_pair(x, y));
                }
            }
        }
        return -1;
    }
};
