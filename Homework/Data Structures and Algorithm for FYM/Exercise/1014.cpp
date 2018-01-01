// 1014. Find degrees
#include <iostream>
using namespace std;

int main() {
  int t, n, val;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      int sum = 0;
      for (int j = 0; j < n; j++) {
        cin >> val;
        sum = sum + val;
      }
      cout << sum << ' ';
    }
    cout << endl;
  }
}
