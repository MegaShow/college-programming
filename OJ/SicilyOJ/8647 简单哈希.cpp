// 8647. 简单哈希
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
  int num, val;
  cin >> num;
  while (num) {
    vector<list<int> > v(13);
    for (int i = 0; i < num; i++) {
      cin >> val;
      v[val % 13].push_back(val);
    }
    for (int i = 0; i < 13; i++) {
      cout << i << '#';
      list<int>::iterator it = v[i].begin();
      if (it != v[i].end()) {
        cout << *it;
        it++;
      } else cout << "NULL";
      while (it != v[i].end()) {
        cout << ' ' << *it;
        it++;
      }
      cout << endl;
    }
    cin >> num;
  }
}
