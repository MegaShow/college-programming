#include <stdio.h>
#include <stack>
#include <set>
using namespace std;

int main() {
    int t, n, index, count = 0;
    char ss[10], c;
    scanf("%d", &t);
    while (t--) {
        count = 0;
        scanf("%d", &n);
        stack<pair<char, int> > s;
        stack<int> ans;
        set<int> cancel;
        for (int i = 1; i <= n; ++i) {
            scanf("%s", ss);
            if (ss[0] == 'd') {
                s.push(make_pair(ss[0], i));
            } else {
                scanf("%d", &index);
                s.push(make_pair(ss[0], index));
            }
        }

        for (int i = n; i > 0; --i) {
            if (!cancel.count(i)) {
                c = s.top().first;
                if (c == 'c') {
                    index = s.top().second;
                    cancel.insert(index);
                }
                ans.push(i);
                count++;
            }
            s.pop();
        }

        printf("%d\n", count);
        if (!ans.empty()) {
          printf("%d", ans.top());
          ans.pop();
        }
        while (!ans.empty()) {
            printf(" %d", ans.top());
            ans.pop();
        }
        printf("\n");
    }
}
