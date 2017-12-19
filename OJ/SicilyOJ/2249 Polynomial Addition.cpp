// 1007. Polynomial Addition
#include <iostream>
#include <list>
using namespace std;

int main() {
  int num, var, x, n;
  cin >> num;
  while (num--) {
    list<pair<int, int> > li[3];
    for (int i = 0; i < 2; i++) {
      cin >> var;
      for (int j = 0; j < var; j++) {
        cin >> x >> n;
        li[i].push_front(make_pair(x, n));
      }
    }
    auto it0 = li[0].begin();
    auto it1 = li[1].begin();
    while (it0 != li[0].end() && it1 != li[1].end()) {
      if (it0->second == it1->second) {
        if (it0->first + it1->first != 0) {
          li[2].push_front(make_pair(it0->first + it1->first, it0->second));
        }
        it0++;
        it1++;
      } else if (it0->second < it1->second) {
        li[2].push_front(make_pair(it0->first, it0->second));
        it0++;
      } else if (it0->second > it1->second) {
        li[2].push_front(make_pair(it1->first, it1->second));
        it1++;
      }
    }
    while (it0 != li[0].end()) {
      li[2].push_front(make_pair(it0->first, it0->second));
      it0++;
    }
    while (it1 != li[1].end()) {
      li[2].push_front(make_pair(it1->first, it1->second));
      it1++;
    }
    cout << li[2].size() << endl;
    for (auto& node : li[2]) {
      cout << node.first << ' ' << node.second << endl;
    }
  }
}
