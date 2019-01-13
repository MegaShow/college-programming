// 1027. 中缀表达式转后缀表达式
#include <cstdio>

int main() {
  char c, prev = 0, val;
  printf("%c", getchar());
  while ((c = getchar()) != '\n') {
    val = getchar();
    if (c == '*' || c == '/' || c == '%') {
      printf("%c%c", val, c);
    } else if (c == '+' || c == '-') {
      if (prev == '+' || prev == '-') {
        printf("%c%c", prev, val);
      } else {
        printf("%c", val);
      }
      prev = c;
    }
  }
  if (prev == '+' || prev == '-') printf("%c", prev);
}

/*#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
using namespace std;

int main() {
  map<char, int> m;
  m['+'] = m['-'] = 1;
  m['*'] = m['/'] = 2;
  string str;
  stack<char> s;
  vector<char> v;
  cin >> str;
  for (auto &i: str) {
    if (i != '+' && i != '-' && i != '*' && i != '/' && i != '%') v.push_back(i);
    else {
      while (!s.empty() && m[s.top()] >= m[i]) {
        v.push_back(s.top());
        s.pop();
      }
      s.push(i);
    }
  }
  while (!s.empty()) {
    v.push_back(s.top());
    s.pop();
  }
  for (auto &i: v) {
    cout << i;
  }
}*/
