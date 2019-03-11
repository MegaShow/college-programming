#include <cstring>
#include <iostream>

using namespace std;

int main() {
    int n, res = 0;
    cin >> n;
    int val[n];
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    int dp[2][n]; // 0 => inc, 1 => dec
    memset(dp, 0, sizeof(int) * 2 * n);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (val[i] < val[j] && dp[0][i] < dp[0][j] + 1) {
                dp[0][i] = dp[0][j] + 1;
            } else if (val[i] > val[j] && dp[1][i] < dp[1][j] + 1) {
                dp[1][i] = dp[1][j] + 1;
            }
        }
        if (res < dp[0][i] + dp[1][i] + 1) {
            res = dp[0][i] + dp[1][i] + 1;
        }
    }
    cout << res << endl;
}
