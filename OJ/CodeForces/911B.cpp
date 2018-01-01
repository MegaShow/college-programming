// B. Two Cakes
#include <iostream>
using namespace std;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  int max = (a + b) / n;
  for (int i = max; i >= 1; i--) {
    if (a >= i && b >= i && a / i + b / i >= n) {
      cout << i << endl;
      break;
    }
  }
}
