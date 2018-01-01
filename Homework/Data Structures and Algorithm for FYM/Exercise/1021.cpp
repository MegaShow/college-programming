// 1021. 括号匹配
#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

int main() {
  map<char, char> m;
  m[')'] = '(';
  m[']'] = '[';
  m['}'] = '{';
  int t;
  string str;
  cin >> t;
  cin.get();
  while (t--) {
    stack<char> s;
    getline(cin, str);
    bool flag = true;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '(' || str[i] == '[' || str[i] == '{') s.push(str[i]);
      else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
        if (!s.empty() && s.top() == m[str[i]]) s.pop();
        else {
          flag = false;
          break;
        }
      }
    }
    if (s.empty() && flag) cout << "Yes" << endl;
    else cout << "No" << endl;
  }
}
