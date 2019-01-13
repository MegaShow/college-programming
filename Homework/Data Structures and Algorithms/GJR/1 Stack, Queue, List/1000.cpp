// 1000. Bracket Matching
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
  int num;
  string str;
  cin >> num;
  for (int i = 0; i < num; i++) {
    stack<char> s;
    cin >> str;
    for (int j = 0; j < str.size(); j++) {
      if (str[j] == '(' || str[j] == '[' || str[j] == '{') {
        s.push(str[j]);
      } else if (str[j] == ')') {
        if (!s.empty() && s.top() == '(') {
          s.pop();
        } else {
          s.push(str[j]);
          break;
        }
      } else if (str[j] == ']') {
        if (!s.empty() && s.top() == '[') {
          s.pop();
        } else {
          s.push(str[j]);
          break;
        }
      } else if (str[j] == '}') {
        if (!s.empty() && s.top() == '{') {
          s.pop();
        } else {
          s.push(str[j]);
          break;
        }
      } 
    }
    if (s.empty()) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
