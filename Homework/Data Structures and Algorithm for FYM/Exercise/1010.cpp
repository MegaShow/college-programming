// 1010. bracket matching
#include <string>
#include <stack>
#include <map>
using namespace std;

map<char, char> bracket_map = { {'(',')'}, {'[',']'}, {'{','}'} };

bool brackets(string s) {
  stack<char> bracket_stack;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(' || s[i] == '[' || s[i] == '{') bracket_stack.push(s[i]);
    else {
      if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
        if (bracket_stack.empty()) return false;
        if (bracket_map[bracket_stack.top()] == s[i]) bracket_stack.pop();
        else return false;
      }
    }
  }
  return bracket_stack.empty();
}

#include <iostream>
int main() {
  cout << brackets("()") << endl;
  cout << brackets(")[](") << endl;
  cout << brackets("([(){}])") << endl;
}
