// 1013. Tautology
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <cstring>
using namespace std;

bool CaseFunc(string& str);
void DFS(bool arr[], int num, int depth, string& str, map<char, int>& m, bool& out_flag);

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    string str;
    cin >> str;
    cout << str << ':' << (CaseFunc(str) ? "Yes" : "No") << endl;
  }
}

bool CaseFunc(string& str) {
  map<char, int> m;
  for (int i = 0; i < str.size(); i++) {
    if (!m.count(str[i]) && str[i] >= 'a' && str[i] <= 'z') {
      m.insert({ str[i], m.size() });
    }
  }
  bool arr[m.size()];
  bool out_flag = true;
  memset(arr, 0, sizeof(arr));
  DFS(arr, m.size(), 0, str, m, out_flag);
  return out_flag;
}

void DFS(bool arr[], int num, int depth, string& str, map<char, int>& m, bool& out_flag) {
  if (out_flag == false) return;
  if (depth == num) {
    stack<bool> s;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        s.push(arr[m[str[i]]]);
      } else if (str[i] == '~') {
        s.top() = !s.top();
      } else if (str[i] == '*') {
        bool a = s.top();
        s.pop();
        s.top() = a & s.top();
      } else if (str[i] == '+') {
        bool a = s.top();
        s.pop();
        s.top() = a | s.top();
      }
    }
    out_flag = s.top();
    return;
  }
  for (int i = 0; i <= 1; i++) {
    arr[depth] = i;
    DFS(arr, num, depth + 1, str, m, out_flag);
  }
}