// 1005. Tailmon Wants to Make a Big News
#include <iostream>
using namespace std;

int main() {
  int val;
  cin >> val;
  if (val == 1) cout << 1 << endl;
  else if (val == 2) cout << 2 << endl;
  else {
    int fib[val];
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < val; i++) {
      fib[i] = fib[i-1] + fib[i-2];
    }
    cout << fib[val-1] << endl;
  }
}
