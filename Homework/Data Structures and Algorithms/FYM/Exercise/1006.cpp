// 1006. Join two lists
#include <list>
#include <set>
using namespace std;

list<int> join(const  list<int> &a, const list<int> &b) {
  set<int> s;
  for (auto &i: a) {
    s.insert(i);
  }
  list<int> li;
  for (auto &i: b) {
    if (s.count(i)) {
      li.push_back(i);
      s.erase(i);
    }
  }
  return li;
}

#include <iostream>
int main() {
  list<int> li = join({3,4,3,5}, {2,3,2,12,4,4});
  for (auto &i: li) {
    cout << i << ' ';
  }
}
