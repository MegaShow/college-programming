#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    int t, n, m, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        int lambda = n + m - k - 1;
        int a = lambda - m;
        int b = lambda - n;
        if (a < 0) a = 0;
        if (b < 0) b = 0;
        if (lambda < 0) {
            printf("0\n");
        } else {
            printf("%d\n", lambda - a - b);
        }
    }
}
