// 1000. Digit Generator
#include <iostream>
using namespace std;

int main() {
  int num, var, count, p, out;
  cin >> num;
  while (num--) {
    cin >> var;
    count = 0;
    for (int i = var; i; count++) {
      p = i % 10;
      i /= 10;
    }
    bool flag = false;
    for (int i = var - count * 9 + 9 - p + 1; i < var; i++) {
      out = 0;
      for (int j = i; j; j /= 10) {
        out = out + j % 10;
      }
      //cout << out << endl;
      if (out + i == var) {
        out = i;
        flag = true;
        break;
      }
    }
    if (flag) {
      cout << out << endl;
    } else {
      cout << 0 << endl;
    }
  }
}