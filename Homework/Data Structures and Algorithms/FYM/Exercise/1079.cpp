// 1079. size of a set
#include <iostream>
#include <set>
using namespace std;

int main() {
  int t, val, n;
  cin >> t;
  while (t--) {
    set<int> s;
    cin >> val;
    while (val != -1) {
      s.insert(val);
      cin >> val;
    }
    cout << s.size() << endl;
  }
}
