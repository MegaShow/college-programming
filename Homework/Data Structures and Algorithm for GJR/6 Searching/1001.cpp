// 1001. A-B
#include <iostream>
#include <set>
using namespace std;

int main() {
  int case_num, a_num, b_num, val;
  cin >> case_num;
  while (case_num--) {
    cin >> a_num;
    set<int> a;
    for (int i = 0; i < a_num; i++) {
      cin >> val;
      a.insert(val);
    }
    cin >> b_num;
    for (int i = 0; i < b_num; i++) {
      cin >> val;
      if (a.count(val)) a.erase(val);
    }
    set<int>::iterator it = a.begin();
    if (it != a.end()) {
      cout << *it;
      it++;
    }
    while (it != a.end()) {
      cout << ' ' << *it;
      it++;
    }
    cout << endl;
  }
}
