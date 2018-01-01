// 1030. 大数加法
#include <iostream>
#include <string>
#include <list>
using namespace std;

int main() {
  list<int> a, b, c;
  string str;
  cin >> str;
  bool flag = true;
  for (int i = 0; i < str.size(); i++) {
    if (flag && str[i] == '0') continue;
    else if (flag) flag = false;
    a.push_front(str[i] - '0');
  }
  cin >> str;
  flag = true;
  for (int i = 0; i < str.size(); i++) {
    if (flag && str[i] == '0') continue;
    else if (flag) flag = false;
    b.push_front(str[i] - '0');
  }
  auto ita = a.begin();
  auto itb = b.begin();
  int carry = 0;
  while (ita != a.end() && itb != b.end()) {
    c.push_front((carry + *ita + *itb) % 10);
    carry = (carry + *ita + *itb) / 10;
    ita++;
    itb++;
  }
  while (ita != a.end()) {
    c.push_front((carry + *ita) % 10);
    carry = (carry + *ita) / 10;
    ita++;
  }
  while (itb != b.end()) {
    c.push_front((carry + *itb) % 10);
    carry = (carry + *itb) / 10;
    itb++;
  }
  if (carry) c.push_front(carry);
  for (auto &i: c) {
    cout << i;
  }
}
