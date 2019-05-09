#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    stack<int> s;
    for (int i = 0, j = 0; i < n; i++) {
        s.push(a[i]);
        while (j < n) {
            if (s.empty()) break;
            int top = s.top();
            if (top == b[j]) {
                s.pop();
                j++;
            } else {
                break;
            }
        }
    }
    if (s.empty()) {
        cout << "Valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }
}
