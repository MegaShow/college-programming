// 1081. print out all elements in a set
#include <iostream>
#include <set>
using namespace std;

int main() {
  int t, val;
  cin >> t;
  while (t--) {
    set<int> s;
    cin >> val;
    while (val != -1) {
      s.insert(val);
      cin >> val;
    }
    for (auto &i: s) {
      cout << i << ' ';
    }
    cout << endl;
  }
}
