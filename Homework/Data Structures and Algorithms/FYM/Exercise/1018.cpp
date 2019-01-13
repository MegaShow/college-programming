// 1018. 放回取样
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
  int n;
  string str;
  cin >> n;
  while (n) {
    set<string> s;
    for (int i = 0; i < n; i++) {
      cin >> str;
      s.insert(str);
    }
    cout << s.size() << endl;
    cin >> n;
  }
}
