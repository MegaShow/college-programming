// 1028. 后缀表达式计算
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

int main() {
  int t;
  string str;
  cin >> t;
  while (t--) {
    cin >> str;
    stack<double> s;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
        double b = s.top();
        s.pop();
        double a = s.top();
        s.pop();
        switch (str[i]) {
          case '+': a += b; break;
          case '-': a -= b; break;
          case '*': a *= b; break;
          case '/': a /= b; break;
        }
        s.push(a);
      } else {
        s.push(str[i] - 'a' + 1);
      }
    }
    cout << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << s.top() << endl;
  }
}
