// 1023. 找出Mode

typedef int T;  // don't submitt this line, and submit the following implementation.

#include <list>
#include <map>
using namespace std;

list<T> getMode(list<T> ls) {
  map<T, int> m;
  for (auto &i: ls) {
    m[i]++;
  }
  map<int, list<T>, greater<int> > mli;
  for (auto &i: m) {
    mli[i.second].push_back(i.first);
  }
  return mli.begin()->second;
}

#include <iostream>

int main() {
  list<int> li = {1, 2, 4, 2, 4};
  list<int> li2 = getMode(li);
  for (auto &i: li2) {
    cout << i << ' ';
  }
}
