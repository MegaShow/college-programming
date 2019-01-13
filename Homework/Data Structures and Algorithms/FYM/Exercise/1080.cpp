// 1080. check if an element is in a set
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
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> val;
      if (s.count(val)) cout << 1 << endl;
      else cout << 0 << endl;
    }
  }
}
