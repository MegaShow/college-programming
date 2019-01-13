// 1509. Rails
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

int main() {
    int num, val = -1;
    while (cin >> num && num != 0) {
        while (cin >> val && val != 0) {
            queue<int> q;
            stack<int> s;
            q.push(val);
            for (int i = 1; i < num; i++) {
                cin >> val;
                q.push(val);
            }
            for (int i = 1; i <= num; i++) {
                s.push(i);
                while (s.size() && s.top() == q.front()) {
                    s.pop();
                    q.pop();
                }
            }
            cout << (s.size() == 0 ? "Yes" : "No") << endl;
        }
        cout << endl;
    }
}
