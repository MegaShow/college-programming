// 1001. Tailmon's Fibnacci Sequence
#include <iostream>
using namespace std;

const int mod = 1000000007;

int main() {
  int val;
  cin >> val;
  if (val == 1) cout << '1' << endl;
  else if (val == 2) cout << '2' << endl;
  else {
    int fib[val];
    fib[0] = fib[1] = 1;
    int sum[val];
    sum[0] = 1;
    sum[1] = 2;
    for (int i = 2; i < val; i++) {
      fib[i] = (fib[i-1] + fib[i-2]) % mod;
      sum[i] = (sum[i-1] + fib[i]) % mod;
    }
    cout << sum[val-1] << endl;
  }
}
