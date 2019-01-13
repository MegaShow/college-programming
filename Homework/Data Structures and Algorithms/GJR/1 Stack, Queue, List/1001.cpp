// 1001. 后缀表达式计算
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

int main() {
  int num;
  string str;
  cin >> num;
  while(num--) {
    stack<double> s;
    cin >> str;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
        double a = s.top();
        s.pop();
        double b = s.top();
        s.pop();
        switch (str[i]) {
          case '+': s.push(b + a); break;
          case '-': s.push(b - a); break;
          case '*': s.push(b * a); break;
          case '/': s.push(b / a); break;
        }
      } else if (str[i] >= 'a' && str[i] <= 'z') {
        s.push(str[i] - 'a' + 1);
      }
    }
    cout << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << s.top() << endl;
    s.pop();
  }
}
