// 1351. Multi-key Sorting
#include <iostream>
#include <stack>
#include <set>
using namespace std;

int main() {
  int column, opr, val;
  while (cin >> column >> opr) {
    set<int> visit;
    stack<int> column_stack, out_stack;
    for (int i = 0; i < opr; i++) {
      cin >> val;
      column_stack.push(val);
    }
    while (column_stack.size()) {
      int node = column_stack.top();
      column_stack.pop();
      if (!visit.count(node)) {
        out_stack.push(node);
        visit.insert(node);
      }
    }
    cout << out_stack.size() << endl;
    while (out_stack.size()) {
      cout << out_stack.top();
      out_stack.pop();
      if (out_stack.size()) cout << ' ';
    }
    cout << endl;
  }
}
